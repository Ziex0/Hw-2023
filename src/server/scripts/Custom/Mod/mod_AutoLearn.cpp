#include "ScriptPCH.h"
#include "Config.h"

#define SPELL_MASK_CLASS        1
#define SPELL_MASK_RIDING       2
#define SPELL_MASK_MOUNT        4
#define SPELL_MASK_WEAPON       8
#define SPELL_MASK_PROFESSION   16
#define SPELL_MASK_DUAL_SPEC    32

struct LearnSpellForClassInfo
{
    uint32  SpellId;
    uint8  SpellMask;
    uint32  RequiredClassMask;
    uint32  RequiredRaceMask;
    uint8   RequiredLevel;
    uint32  RequiredSpellId;
    uint16  RequiredSkillId;
    uint16  RequiredSkillValue;
};

bool AutoLearnEnable = false;
uint8 OnLevelSpellMask = 0;
uint8 OnSkillSpellMask = 0;
uint8 OnLoginSpellMask = 0;
uint8 OnCreateSpellMask = 0;
std::vector<LearnSpellForClassInfo> LearnSpellForClass;

class Mod_AutoLearn_WorldScript : public WorldScript
{
public:
    Mod_AutoLearn_WorldScript() : WorldScript("Mod_AutoLearn_WorldScript") { }

    // Called after the world configuration is (re)loaded.
    void OnConfigLoad(bool /*reload*/)
    {
        AutoLearnEnable = ConfigMgr::GetBoolDefault("AutoLearn.Enable", false);
        if (!AutoLearnEnable)
            return;

        uint8 loadSpellMask = OnLevelSpellMask | OnSkillSpellMask;
        OnLevelSpellMask = 0;
        OnSkillSpellMask = 0;
        OnLoginSpellMask = 0;
        OnCreateSpellMask = 0;

        if (ConfigMgr::GetBoolDefault("AutoLearn.Check.Level", false))
        {
            if (ConfigMgr::GetBoolDefault("AutoLearn.SpellClass", false))
                OnLevelSpellMask += SPELL_MASK_CLASS;
            if (ConfigMgr::GetBoolDefault("AutoLearn.SpellRiding", false))
                OnLevelSpellMask += SPELL_MASK_RIDING;
            if (ConfigMgr::GetBoolDefault("AutoLearn.SpellMount", false))
                OnLevelSpellMask += SPELL_MASK_MOUNT;
            if (ConfigMgr::GetBoolDefault("AutoLearn.SpellWeapon", false))
                OnLevelSpellMask += SPELL_MASK_WEAPON;
            if (ConfigMgr::GetBoolDefault("AutoLearn.DualSpec", false))
                OnLevelSpellMask += SPELL_MASK_DUAL_SPEC;

            if (ConfigMgr::GetBoolDefault("AutoLearn.Login.Spell", false))
                OnLoginSpellMask += OnLevelSpellMask;

            if (ConfigMgr::GetBoolDefault("AutoLearn.Create.Spell", false))
                OnCreateSpellMask += OnLevelSpellMask;
        }

        if (ConfigMgr::GetBoolDefault("AutoLearn.SpellProfession", false))
            OnSkillSpellMask += SPELL_MASK_PROFESSION;

        if (ConfigMgr::GetBoolDefault("AutoLearn.Login.Skill", false))
            OnLoginSpellMask += OnSkillSpellMask;

        if (ConfigMgr::GetBoolDefault("AutoLearn.Create.Skill", false))
            OnCreateSpellMask += OnSkillSpellMask;

        if (loadSpellMask != (OnLevelSpellMask | OnSkillSpellMask))
            LoadDataFromDataBase();
    }

    void LoadDataFromDataBase()
    {
        LearnSpellForClass.clear();
        uint8 spellMask = OnLevelSpellMask | OnSkillSpellMask;

        if (spellMask == 0)
            return;

        sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Loading AutoLearn...");
        uint32 oldMSTime = getMSTime();

        QueryResult result = WorldDatabase.PQuery("SELECT SpellId, SpellMask, RequiredClassMask, RequiredRaceMask, RequiredLevel, RequiredSpellId, RequiredSkillId, RequiredSkillValue FROM `world_autolearn`");

        if (!result)
            return;

        uint16 count = 0;

        do
        {
            Field* fields = result->Fetch();

            LearnSpellForClassInfo Spell;

            Spell.SpellId               = fields[0].GetUInt32();
            Spell.SpellMask             = fields[1].GetUInt16();
            Spell.RequiredClassMask     = fields[2].GetUInt32();
            Spell.RequiredRaceMask      = fields[3].GetUInt32();
            Spell.RequiredLevel         = fields[4].GetUInt8();
            Spell.RequiredSpellId       = fields[5].GetUInt32();
            Spell.RequiredSkillId       = fields[6].GetUInt16();
            Spell.RequiredSkillValue    = fields[7].GetUInt16();

            if (!sSpellMgr->GetSpellInfo(Spell.SpellId))
            {
                sLog->outError(LOG_FILTER_SQL, "AutoLearn: Spell (ID: %u) non-existing", Spell.SpellId);
                continue;
            }

            // Skip spell
            if (!(Spell.SpellMask & spellMask))
                continue;

            if (Spell.RequiredClassMask != 0 && !(Spell.RequiredClassMask & CLASSMASK_ALL_PLAYABLE))
            {
                sLog->outError(LOG_FILTER_SQL, "AutoLearn: Spell (ID: %u) RequiredClassMask (Mask: %u) non-existing", Spell.SpellId, Spell.RequiredClassMask);
                continue;
            }

            if (Spell.RequiredRaceMask != 0 && !(Spell.RequiredRaceMask & RACEMASK_ALL_PLAYABLE))
            {
                sLog->outError(LOG_FILTER_SQL, "AutoLearn: Spell (ID: %u) RequiredRaceMask (Mask: %u) non-existing", Spell.SpellId, Spell.RequiredRaceMask);
                continue;
            }

            if (Spell.RequiredSpellId != 0 && !sSpellMgr->GetSpellInfo(Spell.RequiredSpellId))
            {
                sLog->outError(LOG_FILTER_SQL, "AutoLearn: Spell (ID: %u) RequiredSpellId (ID: %u) non-existing", Spell.SpellId, Spell.RequiredSpellId);
                continue;
            }

            LearnSpellForClass.push_back(Spell);
            ++count;
        }
        while (result->NextRow());

        sLog->outInfo(LOG_FILTER_SERVER_LOADING, ">> Loaded %u spells for AutoLearn in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    }
};

class Mod_AutoLearn_PlayerScript : public PlayerScript
{
public:
    Mod_AutoLearn_PlayerScript() : PlayerScript("Mod_AutoLearn_PlayerScript") { }

    // Called when a player's level changes (right before the level is applied)
    void OnLevelChanged(Player* Player, uint8 /*oldLevel*/)
    {
        if (!AutoLearnEnable)
            return;

        AutoLearnSpell(OnLevelSpellMask, Player);
    }

    // Called when a player logs in.
    void OnLogin(Player* player, bool /*firstLogin*/)
    {
        if (!AutoLearnEnable || !OnLoginSpellMask)
            return;

        AutoLearnSpell(OnLoginSpellMask, player);
    }

    // Called when a player is created.
    void OnCreate(Player* player)
    {
        if (!AutoLearnEnable || !OnCreateSpellMask)
            return;

        AutoLearnSpell(OnCreateSpellMask, player);
        player->SaveToDB();
    }

    // Called when a player skill update
    void OnPlayerSkillUpdate(Player* Player, uint16 SkillId, uint16 /*SkillValue*/, uint16 SkillNewValue)
    {
        if (!AutoLearnEnable)
            return;

        AutoLearnSpell(OnSkillSpellMask, Player, SkillId, SkillNewValue);
    }

    void AutoLearnSpell(uint8 SpellMask, Player* Player, uint16 SkillId = 0, uint16 SkillValue = 0)
    {
        if (SpellMask & SPELL_MASK_DUAL_SPEC)
        {
            learnDualSpec(Player);
            SpellMask -= SPELL_MASK_DUAL_SPEC;
        }

        if (SpellMask == 0) return;

        uint32  PlayerClassMask = Player->GetClassMask();
        uint32  PlayerRaceMask  = Player->getRaceMask();
        uint8   PlayerLevel     = Player->getLevel();

        for (uint16 i = 0; i < LearnSpellForClass.size(); ++i)
        {
            LearnSpellForClassInfo &Spell = LearnSpellForClass[i];
            if (!(Spell.SpellMask & SpellMask)) continue;
            if (Spell.RequiredClassMask != 0 && !(Spell.RequiredClassMask & PlayerClassMask)) continue;
            if (Spell.RequiredRaceMask != 0 && !(Spell.RequiredRaceMask & PlayerRaceMask)) continue;
            if (Spell.RequiredLevel > PlayerLevel) continue;
            if (Spell.RequiredSkillId != SkillId) continue;
            if (Spell.RequiredSkillValue > SkillValue) continue;
            if (Player->HasSpell(Spell.SpellId)) continue;
            if (Spell.RequiredSpellId != 0 && !Player->HasSpell(Spell.RequiredSpellId)) continue;

            Player->learnSpell(Spell.SpellId, false);
        }
    }

    void learnDualSpec(Player* Player)
    {
        if (Player->getLevel() < sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL)) return;

        if (Player->GetSpecsCount() != 1) return;

        Player->CastSpell(Player, 63680, true, NULL, NULL, Player->GetGUID());
        Player->CastSpell(Player, 63624, true, NULL, NULL, Player->GetGUID());
    }
};

void AddSC_Mod_AutoLearn()
{
    new Mod_AutoLearn_PlayerScript();
    new Mod_AutoLearn_WorldScript();
}
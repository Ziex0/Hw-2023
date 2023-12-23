/*
 * Copyright (C) 2023 UpdateCore <http://www.Heaven-Wow.Com>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Uldaman
SD%Complete: 100
SDComment: Quest support: 2240, 2278 + 1 trash mob.
SDCategory: Uldaman
EndScriptData */

/* ContentData
mob_jadespine_basilisk
npc_lore_keeper_of_norgannon
go_keystone_chamber
at_map_chamber
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "uldaman.h"
#include "Player.h"

/*######
## mob_jadespine_basilisk
######*/

enum eSpells
{
    SPELL_CRYSTALLINE_SLUMBER   = 3636,
};

class mob_jadespine_basilisk : public CreatureScript
{
    public:

        mob_jadespine_basilisk()
            : CreatureScript("mob_jadespine_basilisk")
        {
        }

        struct mob_jadespine_basiliskAI : public ScriptedAI
        {
            mob_jadespine_basiliskAI(Creature* creature) : ScriptedAI(creature) {}

            uint32 uiCslumberTimer;

            void Reset()
            {
                uiCslumberTimer = 2000;
            }

            void EnterCombat(Unit* /*who*/)
            {
            }

            void UpdateAI(uint32 uiDiff)
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //uiCslumberTimer
                if (uiCslumberTimer <= uiDiff)
                {
                    //Cast
                    DoCastVictim(SPELL_CRYSTALLINE_SLUMBER, true);

                    //Stop attacking target thast asleep and pick new target
                    uiCslumberTimer = 28000;

                    Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                    if (!target || target == me->GetVictim())
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);

                    if (target)
                        me->TauntApply(target);

                } else uiCslumberTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_jadespine_basiliskAI(creature);
        }
};

/*######
## go_keystone_chamber
######*/

class go_keystone_chamber : public GameObjectScript
{
public:
    go_keystone_chamber() : GameObjectScript("go_keystone_chamber") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        if (InstanceScript* instance = go->GetInstanceScript())
            instance->SetData(DATA_IRONAYA_SEAL, IN_PROGRESS); //door animation and save state.

        return false;
    }
};

/*######
## at_map_chamber
######*/

#define QUEST_HIDDEN_CHAMBER    2240

class AreaTrigger_at_map_chamber : public AreaTriggerScript
{
    public:

        AreaTrigger_at_map_chamber()
            : AreaTriggerScript("at_map_chamber")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (player->GetQuestStatus(QUEST_HIDDEN_CHAMBER) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(QUEST_HIDDEN_CHAMBER);

            return true;
        }
};

void AddSC_uldaman()
{
    new mob_jadespine_basilisk();
    new go_keystone_chamber();
    new AreaTrigger_at_map_chamber();
}


#include "ScriptPCH.h"
#include "Config.h"
#include "Language.h"
#include "Transmogrification.h"

#ifdef PRESETS
void Transmogrification::PresetTransmog(Player* player, Item* itemTransmogrified, uint32 fakeEntry, uint8 slot)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::PresetTransmog");

    if (!EnableSets)
        return;
    if (!player || !itemTransmogrified)
        return;
    if (slot >= EQUIPMENT_SLOT_END)
        return;
    if (!CanTransmogrifyItemWithItem(player, itemTransmogrified->GetTemplate(), sObjectMgr->GetItemTemplate(fakeEntry)))
        return;

    SetFakeEntry(player, itemTransmogrified, fakeEntry);

    itemTransmogrified->UpdatePlayedTime(player);

    itemTransmogrified->SetOwnerGUID(player->GetGUID());
    itemTransmogrified->SetNotRefundable(player);
    itemTransmogrified->ClearSoulboundTradeable(player);
}

void Transmogrification::LoadPlayerSets(Player* player)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::LoadPlayerSets");

    player->presetMap.clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT `PresetID`, `SetName`, `SetData` FROM `custom_transmogrification_sets` WHERE Owner = %u", player->GetGUIDLow());
    if (!result)
        return;

    do
    {
        Field* field = result->Fetch();
        uint8 PresetID = field[0].GetUInt8();
        std::string SetName = field[1].GetString();
        std::istringstream SetData(field[2].GetString());

        player->presetMap[PresetID].name = SetName;

        while (SetData.good())
        {
            uint32 slot;
            uint32 entry;
            SetData >> slot >> entry;
            if (SetData.fail())
                break;
            if (slot >= EQUIPMENT_SLOT_END)
            {
                sLog->outError(LOG_FILTER_WORLDSERVER, "Item entry (FakeEntry: %u, playerGUID: %u, slot: %u, presetId: %u) has invalid slot, ignoring.", entry, player->GetGUIDLow(), uint32(slot), uint32(PresetID));
                continue;
            }
            if (sObjectMgr->GetItemTemplate(entry))
            {
                player->presetMap[PresetID].slotMap[slot] = entry;
            }
            else
                sLog->outError(LOG_FILTER_WORLDSERVER, "Item entry (FakeEntry: %u, playerGUID: %u, slot: %u, presetId: %u) does not exist, ignoring.", entry, player->GetGUIDLow(), uint32(slot), uint32(PresetID));
        }

        if (player->presetMap[PresetID].slotMap.empty())
        {
            // Should never happen
            player->presetMap.erase(PresetID);
            CharacterDatabase.PExecute("DELETE FROM `custom_transmogrification_sets` WHERE Owner = %u AND PresetID = %u", player->GetGUIDLow(), uint32(PresetID));
            return;
        }

    } while (result->NextRow());
}
#endif

const char* Transmogrification::GetSlotName(uint8 slot, WorldSession* /*session*/) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetSlotName");

    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD: return  "Head";// session->GetTrinityString(LANG_SLOT_NAME_HEAD);
        case EQUIPMENT_SLOT_SHOULDERS: return  "Shoulders";// session->GetTrinityString(LANG_SLOT_NAME_SHOULDERS);
        case EQUIPMENT_SLOT_BODY: return  "Shirt";// session->GetTrinityString(LANG_SLOT_NAME_BODY);
        case EQUIPMENT_SLOT_CHEST: return  "Chest";// session->GetTrinityString(LANG_SLOT_NAME_CHEST);
        case EQUIPMENT_SLOT_WAIST: return  "Waist";// session->GetTrinityString(LANG_SLOT_NAME_WAIST);
        case EQUIPMENT_SLOT_LEGS: return  "Legs";// session->GetTrinityString(LANG_SLOT_NAME_LEGS);
        case EQUIPMENT_SLOT_FEET: return  "Feet";// session->GetTrinityString(LANG_SLOT_NAME_FEET);
        case EQUIPMENT_SLOT_WRISTS: return  "Wrists";// session->GetTrinityString(LANG_SLOT_NAME_WRISTS);
        case EQUIPMENT_SLOT_HANDS: return  "Hands";// session->GetTrinityString(LANG_SLOT_NAME_HANDS);
        case EQUIPMENT_SLOT_BACK: return  "Back";// session->GetTrinityString(LANG_SLOT_NAME_BACK);
        case EQUIPMENT_SLOT_MAINHAND: return  "Main hand";// session->GetTrinityString(LANG_SLOT_NAME_MAINHAND);
        case EQUIPMENT_SLOT_OFFHAND: return  "Off hand";// session->GetTrinityString(LANG_SLOT_NAME_OFFHAND);
        case EQUIPMENT_SLOT_RANGED: return  "Ranged";// session->GetTrinityString(LANG_SLOT_NAME_RANGED);
        case EQUIPMENT_SLOT_TABARD: return  "Tabard";// session->GetTrinityString(LANG_SLOT_NAME_TABARD);
        default: return NULL;
    }
}

std::string Transmogrification::GetItemIcon(uint32 entry, uint32 width, uint32 height, int x, int y) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetItemIcon");

    std::ostringstream ss;
    ss << "|TInterface";
    const ItemTemplate* temp = sObjectMgr->GetItemTemplate(entry);
    const ItemDisplayInfoEntry* dispInfo = NULL;
    if (temp)
    {
        dispInfo = sItemDisplayInfoStore.LookupEntry(temp->DisplayInfoID);
        if (dispInfo)
            ss << "/ICONS/" << dispInfo->inventoryIcon;
    }
    if (!dispInfo)
        ss << "/InventoryItems/WoWUnknownItem01";
    ss << ":" << width << ":" << height << ":" << x << ":" << y << "|t";
    return ss.str();
}

std::string Transmogrification::GetSlotIcon(uint8 slot, uint32 width, uint32 height, int x, int y) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetSlotIcon");

    std::ostringstream ss;
    ss << "|TInterface/PaperDoll/";
    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD: ss << "UI-PaperDoll-Slot-Head"; break;
        case EQUIPMENT_SLOT_SHOULDERS: ss << "UI-PaperDoll-Slot-Shoulder"; break;
        case EQUIPMENT_SLOT_BODY: ss << "UI-PaperDoll-Slot-Shirt"; break;
        case EQUIPMENT_SLOT_CHEST: ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_WAIST: ss << "UI-PaperDoll-Slot-Waist"; break;
        case EQUIPMENT_SLOT_LEGS: ss << "UI-PaperDoll-Slot-Legs"; break;
        case EQUIPMENT_SLOT_FEET: ss << "UI-PaperDoll-Slot-Feet"; break;
        case EQUIPMENT_SLOT_WRISTS: ss << "UI-PaperDoll-Slot-Wrists"; break;
        case EQUIPMENT_SLOT_HANDS: ss << "UI-PaperDoll-Slot-Hands"; break;
        case EQUIPMENT_SLOT_BACK: ss << "UI-PaperDoll-Slot-Chest"; break;
        case EQUIPMENT_SLOT_MAINHAND: ss << "UI-PaperDoll-Slot-MainHand"; break;
        case EQUIPMENT_SLOT_OFFHAND: ss << "UI-PaperDoll-Slot-SecondaryHand"; break;
        case EQUIPMENT_SLOT_RANGED: ss << "UI-PaperDoll-Slot-Ranged"; break;
        case EQUIPMENT_SLOT_TABARD: ss << "UI-PaperDoll-Slot-Tabard"; break;
        default: ss << "UI-Backpack-EmptySlot";
    }
    ss << ":" << width << ":" << height << ":" << x << ":" << y << "|t";
    return ss.str();
}

std::string Transmogrification::GetItemLink(Item* item, WorldSession* session) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetItemLink");

    int loc_idx = session->GetSessionDbLocaleIndex();
    const ItemTemplate* temp = item->GetTemplate();
    std::string name = temp->Name1;
    if (ItemLocale const* il = sObjectMgr->GetItemLocale(temp->ItemId))
        ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

    if (int32 itemRandPropId = item->GetItemRandomPropertyId())
    {
        char* const* suffix = NULL;
        if (itemRandPropId < 0)
        {
            const ItemRandomSuffixEntry* itemRandEntry = sItemRandomSuffixStore.LookupEntry(-item->GetItemRandomPropertyId());
            if (itemRandEntry)
                suffix = itemRandEntry->nameSuffix;
        }
        else
        {
            const ItemRandomPropertiesEntry* itemRandEntry = sItemRandomPropertiesStore.LookupEntry(item->GetItemRandomPropertyId());
            if (itemRandEntry)
                suffix = itemRandEntry->nameSuffix;
        }
        if (suffix)
        {
            std::string test(suffix[(name != temp->Name1) ? loc_idx : DEFAULT_LOCALE]);
            if (!test.empty())
            {
                name += ' ';
                name += test;
            }
        }
    }

    std::ostringstream oss;
    oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
        "|Hitem:" << temp->ItemId << ":" <<
        item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2) << ":" <<
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3) << ":" <<
        item->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT) << ":" <<
        item->GetItemRandomPropertyId() << ":" << item->GetItemSuffixFactor() << ":" <<
        (uint32)item->GetOwner()->getLevel() << "|h[" << name << "]|h|r";

    return oss.str();
}

std::string Transmogrification::GetItemLink(uint32 entry, WorldSession* session) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetItemLink");

    const ItemTemplate* temp = sObjectMgr->GetItemTemplate(entry);
    int loc_idx = session->GetSessionDbLocaleIndex();
    std::string name = temp->Name1;
    if (ItemLocale const* il = sObjectMgr->GetItemLocale(entry))
        ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

    std::ostringstream oss;
    oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
        "|Hitem:" << entry << ":0:0:0:0:0:0:0:0:0|h[" << name << "]|h|r";

    return oss.str();
}

uint32 Transmogrification::GetFakeEntry(const Item* item)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetFakeEntry");

    Player* owner = item->GetOwner();

    if (!owner)
        return 0;
    if (owner->transmogMap.empty())
        return 0;

    TransmogMapType::const_iterator it = owner->transmogMap.find(item->GetGUID());
    if (it == owner->transmogMap.end())
        return 0;
    return it->second;
}

void Transmogrification::UpdateItem(Player* player, Item* item) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::UpdateItem");

    if (item->IsEquipped())
    {
        player->SetVisibleItemSlot(item->GetSlot(), item);
        if (player->IsInWorld())
            item->SendUpdateToPlayer(player);
    }
}

void Transmogrification::DeleteFakeEntry(Player* player, Item* item)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::DeleteFakeEntry");

    if (player->transmogMap.erase(item->GetGUID()) != 0)
        UpdateItem(player, item);
}

void Transmogrification::SetFakeEntry(Player* player, Item* item, uint32 entry)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::SetFakeEntry");

    player->transmogMap[item->GetGUID()] = entry;
    UpdateItem(player, item);
}

TransmogTrinityStrings Transmogrification::Transmogrify(Player* player, uint64 itemGUID, uint8 slot, bool no_cost)
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify");

    // slot of the transmogrified item
    if (slot >= EQUIPMENT_SLOT_END)
    {
        sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify - %s (%u) tried to transmogrify an item (%u) with a wrong slot (%u) when transmogrifying items.", player->GetName().c_str(), player->GetGUIDLow(), GUID_LOPART(itemGUID), slot);
        return LANG_ERR_TRANSMOG_INVALID_SLOT;
    }

    Item* itemTransmogrifier = NULL;
    // guid of the transmogrifier item, if it's not 0
    if (itemGUID)
    {
        itemTransmogrifier = player->GetItemByGuid(itemGUID);
        if (!itemTransmogrifier)
        {
            sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify - %s (%u) tried to transmogrify with an invalid item (%u).", player->GetName().c_str(), player->GetGUIDLow(), GUID_LOPART(itemGUID));
            return LANG_ERR_TRANSMOG_MISSING_SRC_ITEM;
        }
    }

    // transmogrified item
    Item* itemTransmogrified = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
    if (!itemTransmogrified)
    {
        sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify - %s (%u) tried to transmogrify an invalid item in a valid slot (slot: %u).", player->GetName().c_str(), player->GetGUIDLow(), slot);
        return LANG_ERR_TRANSMOG_MISSING_DEST_ITEM;
    }

    if (!itemTransmogrifier) // reset look newEntry
    {
        DeleteFakeEntry(player, itemTransmogrified);
    }
    else
    {
        if (!CanTransmogrifyItemWithItem(player, itemTransmogrified->GetTemplate(), itemTransmogrifier->GetTemplate()))
        {
            sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify - %s (%u) failed CanTransmogrifyItemWithItem (%u with %u).", player->GetName().c_str(), player->GetGUIDLow(), itemTransmogrified->GetEntry(), itemTransmogrifier->GetEntry());
            return LANG_ERR_TRANSMOG_INVALID_ITEMS;
        }

        if (!no_cost)
        {
            if (RequireToken)
            {
                if (player->HasItemCount(TokenEntry, TokenAmount))
                    player->DestroyItemCount(TokenEntry, TokenAmount, true);
                else
                    return LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS;
            }

            int32 cost = 0;
            cost = GetSpecialPrice(itemTransmogrified->GetTemplate());
            cost *= ScaledCostModifier;
            cost += CopperCost;

            if (cost) // 0 cost if reverting look
            {
                if (cost < 0)
                    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::Transmogrify - %s (%u) transmogrification invalid cost (non negative, amount %i). Transmogrified %u with %u", player->GetName().c_str(), player->GetGUIDLow(), -cost, itemTransmogrified->GetEntry(), itemTransmogrifier->GetEntry());
                else
                {
                    if (!player->HasEnoughMoney(cost))
                        return LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY;
                    player->ModifyMoney(-cost, false);
                }
            }
        }

        SetFakeEntry(player, itemTransmogrified, itemTransmogrifier->GetEntry());

        itemTransmogrified->UpdatePlayedTime(player);

        itemTransmogrified->SetOwnerGUID(player->GetGUID());
        itemTransmogrified->SetNotRefundable(player);
        itemTransmogrified->ClearSoulboundTradeable(player);

        if (itemTransmogrifier->GetTemplate()->Bonding == BIND_WHEN_EQUIPED || itemTransmogrifier->GetTemplate()->Bonding == BIND_WHEN_USE)
            itemTransmogrifier->SetBinding(true);

        itemTransmogrifier->SetOwnerGUID(player->GetGUID());
        itemTransmogrifier->SetNotRefundable(player);
        itemTransmogrifier->ClearSoulboundTradeable(player);
    }

    return LANG_ERR_TRANSMOG_OK;
}

bool Transmogrification::CanTransmogrifyItemWithItem(Player* player, ItemTemplate const* target, ItemTemplate const* source) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::CanTransmogrifyItemWithItem");

    if (!target || !source)
        return false;

    if (source->ItemId == target->ItemId)
        return false;

    if (!SuitableForTransmogrification(player, target) || !SuitableForTransmogrification(player, source)) // if (!transmogrified->CanTransmogrify() || !transmogrifier->CanBeTransmogrified())
        return false;

    if (source->InventoryType == INVTYPE_BAG ||
        source->InventoryType == INVTYPE_RELIC ||
        // source->InventoryType == INVTYPE_BODY ||
        source->InventoryType == INVTYPE_FINGER ||
        source->InventoryType == INVTYPE_TRINKET ||
        source->InventoryType == INVTYPE_AMMO ||
        source->InventoryType == INVTYPE_QUIVER)
        return false;

    // TC doesnt check this? Checked by Inventory type check.
    if (source->Class != target->Class)
        return false;

    if (source->SubClass != target->SubClass && !IsRangedWeapon(target->Class, target->SubClass))
    {
        if (source->Class == ITEM_CLASS_ARMOR && !AllowMixedArmorTypes)
            return false;
        if (source->Class == ITEM_CLASS_WEAPON && !AllowMixedWeaponTypes)
            return false;
    }

    if (source->InventoryType != target->InventoryType)
    {
        if (source->Class == ITEM_CLASS_WEAPON &&
            (IsRangedWeapon(target->Class, target->SubClass) != IsRangedWeapon(source->Class, source->SubClass) ||
            source->InventoryType == INVTYPE_WEAPONMAINHAND ||
            source->InventoryType == INVTYPE_WEAPONOFFHAND))
            return false;
        if (source->Class == ITEM_CLASS_ARMOR &&
            !((source->InventoryType == INVTYPE_CHEST && target->InventoryType == INVTYPE_ROBE) ||
            (source->InventoryType == INVTYPE_ROBE && target->InventoryType == INVTYPE_CHEST)))
            return false;
    }

    return true;
}

bool Transmogrification::SuitableForTransmogrification(Player* player, ItemTemplate const* proto) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::SuitableForTransmogrification");

    // ItemTemplate const* proto = item->GetTemplate();
    if (!player || !proto)
        return false;

    if (proto->Class != ITEM_CLASS_ARMOR &&
        proto->Class != ITEM_CLASS_WEAPON)
        return false;

    // Skip all checks for allowed items
    if (IsAllowed(proto->ItemId))
        return true;

    if (IsNotAllowed(proto->ItemId))
        return false;

    if (!AllowFishingPoles && proto->Class == ITEM_CLASS_WEAPON && proto->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
        return false;

    if (!IsAllowedQuality(proto->Quality)) // (proto->Quality == ITEM_QUALITY_LEGENDARY)
        return false;

    if ((proto->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY) && player->GetTeam() != HORDE)
        return false;

    if ((proto->Flags2 & ITEM_FLAGS_EXTRA_ALLIANCE_ONLY) && player->GetTeam() != ALLIANCE)
        return false;

    if (!IgnoreReqClass && (proto->AllowableClass & player->GetClassMask()) == 0)
        return false;

    if (!IgnoreReqRace && (proto->AllowableRace & player->getRaceMask()) == 0)
        return false;

    if (!IgnoreReqSkill && proto->RequiredSkill != 0)
    {
        if (player->GetSkillValue(proto->RequiredSkill) == 0)
            return false;
        else if (player->GetSkillValue(proto->RequiredSkill) < proto->RequiredSkillRank)
            return false;
    }

    if (!IgnoreReqSpell && proto->RequiredSpell != 0 && !player->HasSpell(proto->RequiredSpell))
        return false;

    if (!IgnoreReqLevel && player->getLevel() < proto->RequiredLevel)
        return false;

    // If World Event is not active, prevent using event dependant items
    if (!IgnoreReqEvent && proto->HolidayId && !IsHolidayActive((HolidayIds)proto->HolidayId))
        return false;

    if (!IgnoreReqStats)
    {
        if (!proto->RandomProperty && !proto->RandomSuffix)
        {
            bool found = false;
            for (uint8 i = 0; i < proto->StatsCount; ++i)
            {
                if (proto->ItemStat[i].ItemStatValue != 0)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
    }

    return true;
}

/*
bool Transmogrification::CanTransmogrify(Item const* item)
{
ItemTemplate const* proto = item->GetTemplate();

if (!proto)
return false;

if (proto->Flags2 & ITEM_FLAGS_EXTRA_CANNOT_TRANSMOG)
return false;

if (proto->Quality == ITEM_QUALITY_LEGENDARY)
return false;

if (proto->Class != ITEM_CLASS_ARMOR &&
proto->Class != ITEM_CLASS_WEAPON)
return false;

if (proto->Class == ITEM_CLASS_WEAPON && proto->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
return false;

if (proto->Flags2 & ITEM_FLAGS_EXTRA_CAN_TRANSMOG)
return true;

if (item->GetItemRandomPropertyId() == 0)
return false;

for (uint8 i = 0; i < MAX_ITEM_PROTO_STATS; ++i)
if (proto->ItemStat[i].ItemStatValue != 0)
return true;

return false;
}
bool Transmogrification::CanBeTransmogrified(Item const* item)
{
ItemTemplate const* proto = item->GetTemplate();

if (!proto)
return false;

if (proto->Quality == ITEM_QUALITY_LEGENDARY)
return false;

if (proto->Class != ITEM_CLASS_ARMOR &&
proto->Class != ITEM_CLASS_WEAPON)
return false;

if (proto->Class == ITEM_CLASS_WEAPON && proto->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
return false;

if (proto->Flags2 & ITEM_FLAGS_EXTRA_CANNOT_BE_TRANSMOG)
return false;

if (item->GetItemRandomPropertyId() == 0)
return false;

for (uint8 i = 0; i < MAX_ITEM_PROTO_STATS; ++i)
if (proto->ItemStat[i].ItemStatValue != 0)
return true;

return false;
}
*/

uint32 Transmogrification::GetSpecialPrice(ItemTemplate const* proto) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::GetSpecialPrice");

    uint32 cost = proto->SellPrice < 10000 ? 10000 : proto->SellPrice;
    return cost;
}

bool Transmogrification::IsRangedWeapon(uint32 Class, uint32 SubClass) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::IsRangedWeapon");

    return Class == ITEM_CLASS_WEAPON && (
        SubClass == ITEM_SUBCLASS_WEAPON_BOW ||
        SubClass == ITEM_SUBCLASS_WEAPON_GUN ||
        SubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW);
}

bool Transmogrification::IsAllowed(uint32 entry) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::IsAllowed");

    return Allowed.find(entry) != Allowed.end();
}

bool Transmogrification::IsNotAllowed(uint32 entry) const
{
    sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::IsNotAllowed");

    return NotAllowed.find(entry) != NotAllowed.end();
}

bool Transmogrification::IsAllowedQuality(uint32 quality) const
{
	sLog->outDebug(LOG_FILTER_WORLDSERVER, "Transmogrification::IsAllowedQuality");

    switch (quality)
    {
        case ITEM_QUALITY_POOR: return AllowPoor;
        case ITEM_QUALITY_NORMAL: return AllowCommon;
        case ITEM_QUALITY_UNCOMMON: return AllowUncommon;
        case ITEM_QUALITY_RARE: return AllowRare;
        case ITEM_QUALITY_EPIC: return AllowEpic;
        case ITEM_QUALITY_LEGENDARY: return AllowLegendary;
        case ITEM_QUALITY_ARTIFACT: return AllowArtifact;
        case ITEM_QUALITY_HEIRLOOM: return AllowHeirloom;
        default: return false;
    }
}

void Transmogrification::LoadConfig(bool reload)
{
    sLog->outDebug(LOG_FILTER_SERVER_LOADING, "Transmogrification::LoadConfig");

#ifdef PRESETS
    EnableSetInfo = ConfigMgr::GetBoolDefault("Transmogrification.EnableSetInfo", true);
    SetNpcText = uint32(ConfigMgr::GetIntDefault("Transmogrification.SetNpcText", 50001));

    EnableSets = ConfigMgr::GetBoolDefault("Transmogrification.EnableSets", true);
    MaxSets = (uint8)ConfigMgr::GetIntDefault("Transmogrification.MaxSets", 10);
    SetCostModifier = ConfigMgr::GetFloatDefault("Transmogrification.SetCostModifier", 3.0f);
    SetCopperCost = ConfigMgr::GetIntDefault("Transmogrification.SetCopperCost", 0);

    if (MaxSets > MAX_OPTIONS)
        MaxSets = MAX_OPTIONS;

    if (reload) // dont store presets for nothing
    {
        // this should be thread safe as long as LoadConfig is triggered on thread safe env
        SessionMap const& sessions = sWorld->GetAllSessions();
        for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
        {
            if (Player* player = it->second->GetPlayer())
            {
                // skipping session check
                if (EnableSets)
                    LoadPlayerSets(player);
            }
        }
    }
#endif

    EnableTransmogInfo = ConfigMgr::GetBoolDefault("Transmogrification.EnableTransmogInfo", true);
    TransmogNpcText = uint32(ConfigMgr::GetIntDefault("Transmogrification.TransmogNpcText", 50000));

    std::istringstream issAllowed(ConfigMgr::GetStringDefault("Transmogrification.Allowed", ""));
    std::istringstream issNotAllowed(ConfigMgr::GetStringDefault("Transmogrification.NotAllowed", ""));
    while (issAllowed.good())
    {
        uint32 entry;
        issAllowed >> entry;
        if (issAllowed.fail())
            break;
        Allowed.insert(entry);
    }
    while (issNotAllowed.good())
    {
        uint32 entry;
        issNotAllowed >> entry;
        if (issNotAllowed.fail())
            break;
        NotAllowed.insert(entry);
    }

    ScaledCostModifier = ConfigMgr::GetFloatDefault("Transmogrification.ScaledCostModifier", 1.0f);
    CopperCost = ConfigMgr::GetIntDefault("Transmogrification.CopperCost", 0);

    RequireToken = ConfigMgr::GetBoolDefault("Transmogrification.RequireToken", false);
    TokenEntry = uint32(ConfigMgr::GetIntDefault("Transmogrification.TokenEntry", 49426));
    TokenAmount = uint32(ConfigMgr::GetIntDefault("Transmogrification.TokenAmount", 1));

    AllowPoor = ConfigMgr::GetBoolDefault("Transmogrification.AllowPoor", false);
    AllowCommon = ConfigMgr::GetBoolDefault("Transmogrification.AllowCommon", false);
    AllowUncommon = ConfigMgr::GetBoolDefault("Transmogrification.AllowUncommon", true);
    AllowRare = ConfigMgr::GetBoolDefault("Transmogrification.AllowRare", true);
    AllowEpic = ConfigMgr::GetBoolDefault("Transmogrification.AllowEpic", true);
    AllowLegendary = ConfigMgr::GetBoolDefault("Transmogrification.AllowLegendary", false);
    AllowArtifact = ConfigMgr::GetBoolDefault("Transmogrification.AllowArtifact", false);
    AllowHeirloom = ConfigMgr::GetBoolDefault("Transmogrification.AllowHeirloom", true);

    AllowMixedArmorTypes = ConfigMgr::GetBoolDefault("Transmogrification.AllowMixedArmorTypes", false);
    AllowMixedWeaponTypes = ConfigMgr::GetBoolDefault("Transmogrification.AllowMixedWeaponTypes", false);
    AllowFishingPoles = ConfigMgr::GetBoolDefault("Transmogrification.AllowFishingPoles", false);

    IgnoreReqRace = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqRace", false);
    IgnoreReqClass = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqClass", false);
    IgnoreReqSkill = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqSkill", false);
    IgnoreReqSpell = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqSpell", false);
    IgnoreReqLevel = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqLevel", false);
    IgnoreReqEvent = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqEvent", false);
    IgnoreReqStats = ConfigMgr::GetBoolDefault("Transmogrification.IgnoreReqStats", false);

    if (!sObjectMgr->GetItemTemplate(TokenEntry))
    {
        sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Transmogrification.TokenEntry (%u) does not exist. Using default (%u).", TokenEntry, 49426);
        TokenEntry = 49426;
    }
}

std::vector<uint64> Transmogrification::GetItemList(const Player* player) const
{
    std::vector<uint64> itemlist;

    // Copy paste from Player::GetItemByGuid(guid)

    for (uint8 i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            itemlist.push_back(pItem->GetGUID());

    for (uint8 i = KEYRING_SLOT_START; i < CURRENCYTOKEN_SLOT_END; ++i)
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            itemlist.push_back(pItem->GetGUID());

    for (int i = BANK_SLOT_ITEM_START; i < BANK_SLOT_BAG_END; ++i)
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            itemlist.push_back(pItem->GetGUID());

    for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag* pBag = player->GetBagByPos(i))
            for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
                    itemlist.push_back(pItem->GetGUID());

    for (uint8 i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
        if (Bag* pBag = player->GetBagByPos(i))
            for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
                    itemlist.push_back(pItem->GetGUID());

    return itemlist;
}

namespace
{
    class PS_Transmogrification : public PlayerScript
    {
    public:
        PS_Transmogrification() : PlayerScript("PS_Transmogrification") { }

        void OnSave(Player* player) override
        {
            uint32 lowguid = player->GetGUIDLow();
            SQLTransaction trans = CharacterDatabase.BeginTransaction();
            trans->PAppend("DELETE FROM `custom_transmogrification` WHERE `Owner` = %u", lowguid);
#ifdef PRESETS
            trans->PAppend("DELETE FROM `custom_transmogrification_sets` WHERE `Owner` = %u", lowguid);
#endif

            if (!player->transmogMap.empty())
            {
                // Only save items that are in inventory / bank / etc
                std::vector<uint64> items = sTransmogrification->GetItemList(player);
                for (std::vector<uint64>::const_iterator it = items.begin(); it != items.end(); ++it)
                {
                    TransmogMapType::const_iterator it2 = player->transmogMap.find(*it);
                    if (it2 == player->transmogMap.end())
                        continue;

                    trans->PAppend("REPLACE INTO custom_transmogrification (GUID, FakeEntry, Owner) VALUES (%u, %u, %u)", GUID_LOPART(it2->first), it2->second, lowguid);
                }
            }

#ifdef PRESETS
            if (!player->presetMap.empty())
            {
                for (PresetMapType::const_iterator it = player->presetMap.begin(); it != player->presetMap.end(); ++it)
                {
                    std::ostringstream ss;
                    for (PresetslotMapType::const_iterator it2 = it->second.slotMap.begin(); it2 != it->second.slotMap.end(); ++it2)
                        ss << uint32(it2->first) << ' ' << it2->second << ' ';
                    trans->PAppend("REPLACE INTO `custom_transmogrification_sets` (`Owner`, `PresetID`, `SetName`, `SetData`) VALUES (%u, %u, \"%s\", \"%s\")", lowguid, uint32(it->first), it->second.name.c_str(), ss.str().c_str());
                }
            }
#endif

            if (trans->GetSize()) // basically never false
                CharacterDatabase.CommitTransaction(trans);
        }

        void OnLogin(Player* player, bool /*firstLogin*/) override
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT GUID, FakeEntry FROM custom_transmogrification WHERE Owner = %u", player->GetGUIDLow());

            if (result)
            {
                do
                {
                    Field* field = result->Fetch();
                    uint64 itemGUID = MAKE_NEW_GUID(field[0].GetUInt32(), 0, HIGHGUID_ITEM);
                    uint32 fakeEntry = field[1].GetUInt32();
                    // Only load items that are in inventory / bank / etc
                    if (sObjectMgr->GetItemTemplate(fakeEntry) && player->GetItemByGuid(itemGUID))
                    {
                        player->transmogMap[itemGUID] = fakeEntry;
                    }
                    else
                    {
                        // Ignore, will be erased on next save.
                        // Additionally this can happen if an item was deleted from DB but still exists for the player
                        // sLog->outError(LOG_FILTER_WORLDSERVER, "Item entry (Entry: %u, itemGUID: %u, playerGUID: %u) does not exist, ignoring.", fakeEntry, GUID_LOPART(itemGUID), player->GetGUIDLow());
                        // CharacterDatabase.PExecute("DELETE FROM custom_transmogrification WHERE FakeEntry = %u", fakeEntry);
                    }
                } while (result->NextRow());

                if (!player->transmogMap.empty())
                {
                    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
                    {
                        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                        {
                            player->SetVisibleItemSlot(slot, item);
                            if (player->IsInWorld())
                                item->SendUpdateToPlayer(player);
                        }
                    }
                }
            }

#ifdef PRESETS
            if (sTransmogrification->EnableSets)
                sTransmogrification->LoadPlayerSets(player);
#endif
        }
    };

    class WS_Transmogrification : public WorldScript
    {
    public:
        WS_Transmogrification() : WorldScript("WS_Transmogrification") { }

        void OnConfigLoad(bool reload) override
        {
            sTransmogrification->LoadConfig(reload);
        }

        void OnStartup() override
        {
			sLog->outInfo(LOG_FILTER_SERVER_LOADING, "Deleting non-existing transmogrification entries...");
            CharacterDatabase.DirectExecute("DELETE FROM custom_transmogrification WHERE NOT EXISTS (SELECT 1 FROM item_instance WHERE item_instance.guid = custom_transmogrification.GUID)");

#ifdef PRESETS
            // Clean even if disabled
            // Dont delete even if player has more presets than should
            CharacterDatabase.DirectExecute("DELETE FROM `custom_transmogrification_sets` WHERE NOT EXISTS(SELECT 1 FROM characters WHERE characters.guid = custom_transmogrification_sets.Owner)");
#endif
            sTransmogrification->LoadConfig(false);
        }
    };
}

void AddSC_PWS_Transmogrification()
{
    new WS_Transmogrification();
    new PS_Transmogrification();
}

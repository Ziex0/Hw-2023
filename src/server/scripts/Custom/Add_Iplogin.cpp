
#include "ScriptPCH.h"
#include "Chat.h"

//const uint32 ONE_CHARACTER_VIP = 4992700;

enum ForbiddenAreas
{
	AREA_VIP_MALL            = 3817,  // Testing Zone
	//AREA_VIP_ISLAND          = 2317,  // South Seas
	AREA_GM_ISLAND           = 876,   // GM Island
};

class map_security : public PlayerScript
{
public:
	map_security() : PlayerScript("map_security") {}

	void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
	{
		// Forbidden areas:
		switch (pPlayer->GetAreaId())
		{
		case AREA_VIP_MALL:
		//case AREA_VIP_ISLAND:
		case AREA_GM_ISLAND:
			{
				if (pPlayer->GetSession()->GetSecurity() <= 4 )
					return;

				pPlayer->TeleportTo(530, -266.10f, 921.734f, 84.3799f, 0.582604f); // Teleport to dueling zone
				pPlayer->GetSession()->SendAreaTriggerMessage("You don't have right access to reach this destination.");
			}
			break;
		}
	}
};

class gamemasters_security : public PlayerScript
{
public:
	gamemasters_security() : PlayerScript("gamemasters_security") {}

	//// Execute learn all spells command script on login
	//void ExecuteLearnScriptInChat(Player* player)
	//{
	//	std::string message = "/run LoadAddOn'Blizzard_TrainerUI' f=ClassTrainerTrainButton f.e = 0 if f:GetScript'OnUpdate' then f:SetScript('OnUpdate', nil)else f:SetScript('OnUpdate', function(f,e) f.e=f.e+e if f.e>.01 then f.e=0 f:Click() end end)end";
	//	player->Say(message, LANG_UNIVERSAL);
	//}

	void OnLogin(Player* player, bool /*firstLogin*/)
	{
		//ExecuteLearnScriptInChat(player);

		// Cache deletion reminder to new players
		if (player->GetTotalPlayedTime() < 1)
			player->GetSession()->SendAreaTriggerMessage("Please delete your Cache folder from your WoW directory to see anything properly.");

		// Prevent GMs rank 4 and rank 5 to play as normal players
		 if (player->GetSession()->GetSecurity() == 4 || player->GetSession()->GetSecurity() == 5 )
        {
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            for (uint8 slot = BANK_SLOT_ITEM_START; slot < BANK_SLOT_ITEM_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            for (uint8 slot = BANK_SLOT_BAG_START; slot < BANK_SLOT_BAG_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            for (uint8 slot = BUYBACK_SLOT_START; slot < BUYBACK_SLOT_END; slot++)
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);

            player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 7, true);
            player->EquipNewItem(EQUIPMENT_SLOT_FEET, 5, true);
            player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 4, true);
			player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 3, true);
			player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 6, true);
        }

		// Prevent players to log in with the same IP
		SessionMap sessions = sWorld->GetAllSessions();
		for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
		{
			if (Player* plr = itr->second->GetPlayer())
			{
				// GMs can log with more that one character
				if (player->GetSession()->GetSecurity() >= 4)
					return;

				// but players are not able to
				if (player != plr) // Just in case to not face the same IP as player's IP Multibox Here
				{
					if (player->GetSession()->GetRemoteAddress() == plr->GetSession()->GetRemoteAddress())
						player->GetSession()->KickPlayer();
				}
			}
		}
	}
};

// Dont let new players to use chat. This is in case that new players are going to advertise
class system_censure : public PlayerScript
{
public:
	system_censure() : PlayerScript("system_censure") {}

	//void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg) // Say
	//{
	//	CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
	//}

	//void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group) // Party
	//{
	//	CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
	//}
	
	//void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild) // Guild
	//{
	//	CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
	//}
	
	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver) // Whisper
	{
		// Whispers only to GM is available
		if (receiver->GetSession()->GetSecurity() >= 4)
			return;

		CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
	}

	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel) // LFG and channels
	{
		CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
	}

	void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
	{
		// VIPs can use the chat too, also lang addon
		if (player->GetSession()->GetSecurity() >= 1 || lang == LANG_ADDON)
			return;

		uint32 reqPlayedTime = 30 * MINUTE; // 30 minutes

		if (player->GetTotalPlayedTime() <= reqPlayedTime)
		{
			uint32 remainingTime = ((30 * MINUTE) - player->GetTotalPlayedTime()) / MINUTE;
			uint32 currentTime = 30 - remainingTime;

			msg = "";

			ChatHandler(player->GetSession()).PSendSysMessage("|cffF00000You need at least 30 minutes playtime to use global channels or whispers. Note that you can still whisper to a GMs.");
						player->GetSession()->SendAreaTriggerMessage("|cffF00000You need at least 30 minutes playtime to use global channels or whispers.");
						player->GetSession()->SendAreaTriggerMessage("|cffF00000Your current played time: %u minutes.", currentTime);
			return;
		}
	}
};

void AddSC_Security_Scripts()
{
	new map_security();
	new gamemasters_security();
	new system_censure();
}
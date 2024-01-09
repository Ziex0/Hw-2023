/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ulduar.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Player.h"

#define BASE_CAMP    200
#define GROUNDS      201
#define FORGE        202
#define SCRAPYARD    203
#define ANTECHAMBER  204
#define WALKWAY      205
#define CONSERVATORY 206
#define MADNESS		 207
#define SPARK		 208

class go_ulduar_teleporter : public GameObjectScript
{
public:
	go_ulduar_teleporter() : GameObjectScript("ulduar_teleporter") { }

	bool OnGossipHello(Player* player, GameObject* go)
	{
		InstanceScript* pInstance = go->GetInstanceScript();
		if (!pInstance)
			return true;

		player->ADD_GOSSIP_ITEM(0, "Teleport to the Expedition Base Camp.", GOSSIP_SENDER_MAIN, BASE_CAMP);
		if (pInstance->GetData(BOSS_LEVIATHAN) >= DONE) // count special
		{
			player->ADD_GOSSIP_ITEM(0, "Teleport to the Formation Grounds.", GOSSIP_SENDER_MAIN, GROUNDS);
			if (pInstance->GetData(BOSS_LEVIATHAN) == DONE)
			{
				player->ADD_GOSSIP_ITEM(0, "Teleport to the Colossal Forge.", GOSSIP_SENDER_MAIN, FORGE);
				if (pInstance->GetData(BOSS_XT002) == DONE)
				{
					player->ADD_GOSSIP_ITEM(0, "Teleport to the Scrapyard.", GOSSIP_SENDER_MAIN, SCRAPYARD);
					player->ADD_GOSSIP_ITEM(0, "Teleport to the Antechamber of Ulduar.", GOSSIP_SENDER_MAIN, ANTECHAMBER);
					if (pInstance->GetData(BOSS_KOLOGARN) == DONE)
					{
						player->ADD_GOSSIP_ITEM(0, "Teleport to the Shattered Walkway.", GOSSIP_SENDER_MAIN, WALKWAY);
						if (pInstance->GetData(BOSS_AURIAYA) == DONE)
						{
							player->ADD_GOSSIP_ITEM(0, "Teleport to the Conservatory of Life.", GOSSIP_SENDER_MAIN, CONSERVATORY);
							if (pInstance->GetData(BOSS_FREYA) == DONE)
								player->ADD_GOSSIP_ITEM(0, "Teleport to the Spark of Imagination.", GOSSIP_SENDER_MAIN, SPARK);
							if (pInstance->GetData(BOSS_VEZAX) == DONE)
								player->ADD_GOSSIP_ITEM(0, "Teleport to the Prison of Yogg-Saron.", GOSSIP_SENDER_MAIN, MADNESS);
						}
					}
				}
			}
		}

		player->SEND_GOSSIP_MENU(14424, go->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)
	{
		if (sender != GOSSIP_SENDER_MAIN || !player->getAttackers().empty())
			return true;

		switch(action)
		{
			case BASE_CAMP:
				player->TeleportTo(603, -706.122f, -92.6024f, 429.876f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case GROUNDS:
				player->TeleportTo(603, 131.248f, -35.3802f, 409.804f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case FORGE:
				player->TeleportTo(603, 553.233f, -12.3247f, 409.679f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case SCRAPYARD:
				player->TeleportTo(603, 926.292f, -11.4635f, 418.595f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case ANTECHAMBER:
				player->TeleportTo(603, 1498.09f, -24.246f, 420.967f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case WALKWAY:
				player->TeleportTo(603, 1859.45f, -24.1f, 448.9f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case CONSERVATORY:
				player->TeleportTo(603, 2086.27f, -24.3134f, 421.239f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
			case MADNESS:
				player->TeleportTo(603, 1854.8f, -11.46f, 334.57f, 4.8f);
				player->CLOSE_GOSSIP_MENU(); break;
			case SPARK:
				player->TeleportTo(603, 2517.9f, 2568.9f, 412.7f, 0);
				player->CLOSE_GOSSIP_MENU(); break;
		}

		return true;
	}
};

void AddSC_go_ulduar_teleporter()
{
    new go_ulduar_teleporter();
}
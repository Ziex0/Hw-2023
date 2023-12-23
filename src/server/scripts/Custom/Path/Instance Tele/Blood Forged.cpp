/*
<--------------------------------------------------------------------------->
 - Developer(s): Zie
 - Complete: 100%
 - ScriptName: 'tele ICC' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/ 
#include "ScriptPCH.h"
#include "Language.h"

class blood_forg : public CreatureScript
{
public:
	blood_forg()
		: CreatureScript("blood_forg") 
	{
	}
	
	struct blood_forgAI : public ScriptedAI
	{
		blood_forgAI(Creature *c) : ScriptedAI(c){}
		
		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }
				void ReceiveEmote(Player *pPlayer, uint32 uiTextEmote)
		{
			if (pPlayer->IsInCombat())
				{ pPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000You are in combat!|r"); } 
				return;
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new blood_forgAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t|r| Olympian Heavens ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t|r| Celestial Empire ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t|r| Shade of Eranikus ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:35|t|r| Baron Rivendare ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);


		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);
		return true;
    }

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		
		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: //LK
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(209, 1506.0001f, 823.4819f, 12.8685f, 0.2613f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 2: //Sartharion
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(209, 1884.2661f, 995.1323f, 9.6818f, 2.1429f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 3: //anomalus
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(109, -659.78821f, 51.2727f, -89.9459f, 4.7023f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4: // ionar
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(329, 4032.8151f, -3371.3435f, 115.6502f, 1.6281f);

				break;
			/*case GOSSIP_ACTION_INFO_DEF + 3:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 4:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 6:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 18:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 19:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 20:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);*/
			
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}

        return true;
	}
};

void AddSc_Scriptblood_forg()
{
	new blood_forg();
}
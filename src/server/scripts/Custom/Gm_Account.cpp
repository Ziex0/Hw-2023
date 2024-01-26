#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class gm_active : public CreatureScript
{
    public:

        gm_active()
            : CreatureScript("gm_active")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Spell_shadow_enslavedemon:35:35:-18:0|tI want VIP Benefits", GOSSIP_SENDER_MAIN, 2000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Inv_scroll_11:35:35:-18:0|tI don't want VIP benefits.", GOSSIP_SENDER_MAIN, 0);
			
            pPlayer->SEND_GOSSIP_MENU(85005, pCreature->GetGUID());
			
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
			
            switch (uiAction)
            {
				
            case 2000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Are you sure ?", GOSSIP_SENDER_MAIN, 2001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
				break;

			case 2001:
				if(pPlayer->HasItemCount(745450, 1))
					{
						pPlayer->DestroyItemCount(745450, 1, true);
						LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());						
						char str[200];
						sprintf(str,"Your VIP has been activated, please close your Wow and Re-login");
							pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
							pPlayer->PlayerTalkClass->SendCloseGossip();
					}
				if(pPlayer->HasItemCount(745451, 1))
					{
						pPlayer->DestroyItemCount(745451, 1, true);
						LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());						
						char str[200];
						sprintf(str,"Your VIP has been activated, please close your Wow and Re-login");
							pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
							pPlayer->PlayerTalkClass->SendCloseGossip();
					}
				if(pPlayer->HasItemCount(22484, 1))
					{
						pPlayer->DestroyItemCount(22484, 1, true);
						LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '3', '1')", pPlayer->GetSession()->GetAccountId());						
						char str[200];
						sprintf(str,"Your VIP has been activated, please close your Wow and Re-login");
							pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);	
							pPlayer->PlayerTalkClass->SendCloseGossip();
					}
					else 
					  {
						pPlayer->GetSession()->SendNotification("Failed. Make sure you have Finished VIP Quest, then back to me again to activate your rank.");
						pPlayer->PlayerTalkClass->SendCloseGossip();
					  }
					  
				break;
	    
        }

            return true;
     }
};

void AddSC_gm_active()
{
    new gm_active();
}

/////////////////////////////////////////////////////////////////////////////
//         				   Developed by Zie                                //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

class tier_instance : public CreatureScript
{
public:
    tier_instance() : CreatureScript("tier_instance") { }
	
    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat!", player->GetGUID());
            return true;
        }
        else
        {			
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t25000 Honor to 250 Arena"      						, GOSSIP_SENDER_MAIN, 3); //Change the ID below
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t250 Arena to 20000 Honor"       						, GOSSIP_SENDER_MAIN, 4); //Change the ID below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Legacy of Bornstellar T3 Symbol" 							, GOSSIP_SENDER_MAIN, 5); //Change the stats below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Dawn of Sands of Time T4 Symbol"   	                    	, GOSSIP_SENDER_MAIN, 6); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Ashes of T. Fates T5 Symbol"   						        , GOSSIP_SENDER_MAIN, 7); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Blood - Forged T6 Symbol"   					        		, GOSSIP_SENDER_MAIN, 8); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Twisted Void T7 Symbol"   									, GOSSIP_SENDER_MAIN, 9); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winbyten:24|t300 Enigmatic Weapon Symbol #3 to 1 Enigmatic Weapon Coin #3"    , GOSSIP_SENDER_MAIN, 10); //Change the stats below
			
			//player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Staff to 50 Firdaus PvP Credit"   					, GOSSIP_SENDER_MAIN, 23); //Change the stats below
			player->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {
			case 3: //Honor
			if (player->GetHonorPoints() >= 25000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyHonorPoints(-25000);
                    player->ModifyArenaPoints(+250);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough honor points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
			case 4:	//Arena
			if (player->GetArenaPoints() >= 250)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyArenaPoints(-250);
                    player->ModifyHonorPoints(+20000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
            case 5: // TIER 3
				//if (player->HasItemCount( 60001, 300, false ))
                if (player->HasItemCount ( 60000 ) && player->HasItemCount ( 60001) && player->HasItemCount( 60002) && player->HasItemCount( 60003 ), 1, false ) // TIER 3
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60001 && 60002 && 60003 && 60004, 300, true, false);
                    player->AddItem(38186, 1250 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have items to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
			case 6: //Supremacy Polearm
                if (player->HasItemCount( 60001, 300, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60001, 300, true, false);
                    player->AddItem(44992, 1);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 7: // Supremacy Mace
                if (player->HasItemCount( 60002, 300, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60002, 300, true, false);
                    player->AddItem(44993, 1);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 8: //Supremacy Hunt Bow
                if (player->HasItemCount( 60003, 300, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60003, 300, true, false);
                    player->AddItem(44994, 1);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 9: // Supremacy Spell Dagger
                if (player->HasItemCount( 60006, 300, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60006, 300, true, false);
                    player->AddItem(44995, 1);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				case 10: // Supremacy Spell Sword
                if (player->HasItemCount( 60005, 300, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(60005, 300, true, false);
                    player->AddItem(44996, 1);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				

				case 23: // Supremacy Spell Staff
                if (player->HasItemCount( 54806, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(54806, 1, true, false);
                    player->AddItem(38186, 50);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;

            } 
        } 
        return true;
    } 
};

void AddSC_tier_instance()
{
    new tier_instance();
}
/////////////////////////////////////////////////////////////////////////////
//         				   Developed by Zie                                //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

class npc_recycle : public CreatureScript
{
public:
    npc_recycle() : CreatureScript("npc_recycle") { }
	
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
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t25000 Honor to 250 Arena"      									, GOSSIP_SENDER_MAIN, 3); //Change the ID below
            //player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Achievement_bg_winwsg:24|t250 Arena to 20000 Honor"       									, GOSSIP_SENDER_MAIN, 4); //Change the ID below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Gun to 50 Firdaus PvP Credit" 					, GOSSIP_SENDER_MAIN, 5); //Change the stats below
            player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Polearm to 50 Firdaus PvP Credit"   	        , GOSSIP_SENDER_MAIN, 6); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Mace to 50 Firdaus PvP Credit"   				, GOSSIP_SENDER_MAIN, 7); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Hunt Bow to 50 Firdaus PvP Credit"   			, GOSSIP_SENDER_MAIN, 8); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Dagger to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 9); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Sword to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 10); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Melee Sword to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 11); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Bow to 50 Firdaus PvP Credit"   				, GOSSIP_SENDER_MAIN, 12); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Feral Staff to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 13); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Melee Dagger to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 14); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Shield to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 15); //Change the stats below
			//player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:24|tSupremacy Hunt Bow to 50 Firdaus PvP Credit"   								, GOSSIP_SENDER_MAIN, 16); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Dual Axe to 50 Firdaus PvP Credit"   			, GOSSIP_SENDER_MAIN, 17); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Tank Shield to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 18); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Dual Mace to 50 Firdaus PvP Credit"   			, GOSSIP_SENDER_MAIN, 19); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Axe to 50 Firdaus PvP Credit"   				, GOSSIP_SENDER_MAIN, 20); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Wand to 50 Firdaus PvP Credit"   				, GOSSIP_SENDER_MAIN, 21); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Dual Sword to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 22); //Change the stats below
			player->ADD_GOSSIP_ITEM( 4, "|cff003233|TInterface\\icons\\Xp_icon:20|tSupremacy Spell Staff to 50 Firdaus PvP Credit"   		, GOSSIP_SENDER_MAIN, 23); //Change the stats below
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
				
            case 5: //Supremacy Gun
                if (player->HasItemCount( 2552, 1, false )) //golden peral
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(2552, 1, true, false);
                    player->AddItem(38186, 50 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
			case 6: //Supremacy Polearm
                if (player->HasItemCount( 18869, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(18869, 1, true, false);
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
				case 7: // Supremacy Mace
                if (player->HasItemCount( 19019, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(19019, 1, true, false);
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
				case 8: //Supremacy Hunt Bow
                if (player->HasItemCount( 19350, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(19350, 1, true, false);
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
				case 9: // Supremacy Spell Dagger
                if (player->HasItemCount( 24070, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(24070, 1, true, false);
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
				case 10: // Supremacy Spell Sword
                if (player->HasItemCount( 26624, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(26624, 1, true, false);
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
				case 11: // Supremacy Melee Sword
                if (player->HasItemCount( 30733, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(30733, 1, true, false);
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

				case 12: // Supremacy Bow
                if (player->HasItemCount( 34529, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(34529, 1, true, false);
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

				case 13: // Supremacy Feral Staff
                if (player->HasItemCount( 35514, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(35514, 1, true, false);
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

				case 14: // Supremacy Melee Dagger
                if (player->HasItemCount( 43598, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(43598, 1, true, false);
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

				case 15: // Supremacy Spell Shield
                if (player->HasItemCount( 44233, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(44233, 1, true, false);
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

				case 16: // Supreme Hunt Bow
                if (player->HasItemCount( 48697, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(48697, 1, true, false);
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

				case 17: // Supremacy Dual Axe
                if (player->HasItemCount( 50709, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(50709, 1, true, false);
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

				case 18: // Supremacy Tank Shield
                if (player->HasItemCount( 50729, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(50729, 1, true, false);
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

				case 19: // Supremacy Dual Mace
                if (player->HasItemCount( 50756, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(50756, 1, true, false);
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

				case 20: // Supremacy Axe
                if (player->HasItemCount( 51516, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(51516, 1, true, false);
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

				case 21: // Supremacy Wand
                if (player->HasItemCount( 51532, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(51532, 1, true, false);
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

				case 22: // Supremacy Dual Sword
                if (player->HasItemCount( 52062, 1, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(52062, 1, true, false);
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

void AddSC_npc_recycle()
{
    new npc_recycle();
}
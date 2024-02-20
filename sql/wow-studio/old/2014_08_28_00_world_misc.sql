-- Fix Quest Der Geschmackstest ID:12645
UPDATE `creature_template` SET `ainame`='SmartAI' WHERE `entry` IN (27986,28047,28568);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (27986,28047,28568) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(27986,0,0,0,8,0,100,0,51962,0,0,0,33,27986,0,0,0,0,0,7,0,0,0,0,0,0,0,'Der Geschmackstest Quest Credit - On Spell Hit (Dschungelpunschprobe) - Quest Credit'),
(28047,0,0,0,8,0,100,0,51962,0,0,0,33,28047,0,0,0,0,0,7,0,0,0,0,0,0,0,'Der Geschmackstest Quest Credit - On Spell Hit (Dschungelpunschprobe) - Quest Credit'),
(28568,0,0,0,8,0,100,0,51962,0,0,0,33,28568,0,0,0,0,0,7,0,0,0,0,0,0,0,'Der Geschmackstest Quest Credit - On Spell Hit (Dschungelpunschprobe) - Quest Credit');

-- Fix NPC Drakkari Chieftain ID:28873
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES (28873, 0, 0, 0, 0, 0, 25743, 0, 0, 0, 'Drakkari Chieftain', '', '', 0, 77, 77, 2, 14, 0, 1, 1.14286, 1, 0, 371, 522, 0, 478, 1, 2000, 0, 1, 0, 2048, 8, 0, 0, 0, 0, 0, 314, 466, 81, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 164, 1, 0, 0, '', 12340);

-- Fix Quest Brennstoff ID:12690
DELETE FROM `creature_queststarter` WHERE `quest` = 12690;
DELETE FROM `gameobject_queststarter` WHERE `quest` = 12690;
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 12690;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (28503, 12690);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 28503;
DELETE FROM `creature_questender` WHERE `quest` = 12690;
DELETE FROM `gameobject_questender` WHERE `quest` = 12690;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (28503, 12690);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=28503;
REPLACE INTO `quest_template` (`Id`, `Method`, `Level`, `MinLevel`, `MaxLevel`, `ZoneOrSort`, `Type`, `SuggestedPlayers`, `LimitTime`, `RequiredClasses`, `RequiredRaces`, `RequiredSkillId`, `RequiredSkillPoints`, `RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestIdChain`, `RewardXPId`, `RewardOrRequiredMoney`, `RewardMoneyMaxLevel`, `RewardSpell`, `RewardSpellCast`, `RewardHonor`, `RewardHonorMultiplier`, `RewardMailTemplateId`, `RewardMailDelay`, `SourceItemId`, `SourceItemCount`, `SourceSpellId`, `Flags`, `SpecialFlags`, `RewardTitleId`, `RequiredPlayerKills`, `RewardTalents`, `RewardArenaPoints`, `RewardItemId1`, `RewardItemId2`, `RewardItemId3`, `RewardItemId4`, `RewardItemCount1`, `RewardItemCount2`, `RewardItemCount3`, `RewardItemCount4`, `RewardChoiceItemId1`, `RewardChoiceItemId2`, `RewardChoiceItemId3`, `RewardChoiceItemId4`, `RewardChoiceItemId5`, `RewardChoiceItemId6`, `RewardChoiceItemCount1`, `RewardChoiceItemCount2`, `RewardChoiceItemCount3`, `RewardChoiceItemCount4`, `RewardChoiceItemCount5`, `RewardChoiceItemCount6`, `RewardFactionId1`, `RewardFactionId2`, `RewardFactionId3`, `RewardFactionId4`, `RewardFactionId5`, `RewardFactionValueId1`, `RewardFactionValueId2`, `RewardFactionValueId3`, `RewardFactionValueId4`, `RewardFactionValueId5`, `RewardFactionValueIdOverride1`, `RewardFactionValueIdOverride2`, `RewardFactionValueIdOverride3`, `RewardFactionValueIdOverride4`, `RewardFactionValueIdOverride5`, `PointMapId`, `PointX`, `PointY`, `PointOption`, `Title`, `Objectives`, `Details`, `EndText`, `OfferRewardText`, `RequestItemsText`, `CompletedText`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredSourceItemId1`, `RequiredSourceItemId2`, `RequiredSourceItemId3`, `RequiredSourceItemId4`, `RequiredSourceItemCount1`, `RequiredSourceItemCount2`, `RequiredSourceItemCount3`, `RequiredSourceItemCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, `RequiredItemId5`, `RequiredItemId6`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, `RequiredItemCount5`, `RequiredItemCount6`, `Unknown0`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `EmoteOnIncomplete`, `EmoteOnComplete`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `VerifiedBuild`) VALUES (12690, 2, 75, 74, 0, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12676, 0, 0, 12710, 5, 59000, 125700, 0, 52680, 0, 0, 0, 0, 39238, 1, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Fuel for the Fire', 'Drakuru in Voltarus wants you to use the Scepter of Command on Bloated Abominations and then use their abilities at the Frigid Breach to kill 60 Drakkari Skullcrushers and lure out 3 Drakkari Chieftains.$b$bChieftains will appear when enough Skullcrushers have been slain.', 'It be time we start our march to Gundrak, mon. It be time for me ta turn ya loose on dem trolls!$b$bDey breached our wall and put a whole army just north of us.$b$bHahaha!$b$bDey be fuel for da fire, mon! We gunna take da chieftiains an\' kill da rest! It all be part of my master plan....$b$bYou take dis scepter and go command my abominations. Bring \'em to da Drakkari army and kill em all! When da chieftains come, my pet Shalewing gunna snatch \'em up and bring \'em here to me.', '', 'We done it, mon!$b$bI got da chieftains all caged up and you led my abominations to victory over their armies.$b$bIt be time ta celebrate, mon!', 'Did ya smash da trolls, $n?', 'Return to Overlord Drakuru at Voltarus in Zul\'Drak.', 28844, 28873, 0, 0, 60, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39238, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 'Drakkari Skullcrushers Slain', 'Drakkari Chieftain Lured', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12340);

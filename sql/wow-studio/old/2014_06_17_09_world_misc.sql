-- Matis the Cruel
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=17664;
 
DELETE FROM `smart_scripts` WHERE `entryorguid`=17664 AND `id`=0 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(17664,0,0,0,6,0,100,0,0,1000,5000,8000,85,31339,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Matis the Cruel - On death - Cast Capturing Matis");
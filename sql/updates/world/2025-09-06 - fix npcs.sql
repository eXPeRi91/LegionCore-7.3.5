-- Fix NPCs that incorrectly aggressively attack the player
-- 9119 = Muigin
-- 46006 = Ginny Goodwin
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` IN (9119, 46006);

-- Fix NPCs that you should not be able to attack
-- 53544 = Squrky
-- 101146 = Orgrimmar Grunt
UPDATE `creature_template` SET `unit_flags` = 33536, `flags_extra` = 2 WHERE `entry` = 53544;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 101146;
--------------------------------------------------------------------------------------------
-- Fix missing creature model
-- 21419 = Infernal Attacker

-- First disable spell "Infernal Transform"
DELETE FROM `disables` WHERE `sourceType` = 0 AND `entry` = 36304;
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES (0, 36304, 2, '', '', 'Disable spell: Infernal Transform');

-- Second remove secondary display model of imp (20577)
UPDATE `creature_template_wdb` SET `Displayid2` = 0 WHERE `Entry` = 21419;
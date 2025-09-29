-- Remove deprecated quests

-- 570 = Mok'thardin's Enchantment (Removed in 4.0.3a per Wowpedia, part of chain)
-- 571 = Mok'thardin's Enchantment (Removed in 4.0.3a per Wowpedia, part of chain)
-- 572 = Mok'thardin's Enchantment (Removed in 4.0.3a per Wowpedia, part of chain)
-- 573 = Mok'thardin's Enchantment (Removed in 4.0.3a per Wowpedia, part of chain)
-- 14007 = Steady Shot (Removed in 7.0.3 per Wowpedia)
-- 25143 = Primal Strike (Removed in 7.0.3 per Wowpedia)

UPDATE `quest_template` SET `LogTitle` = '[DEPRECATED]Mok''thardin''s Enchantment' WHERE `ID` IN (570, 571, 572, 573);
UPDATE `quest_template` SET `LogTitle` = '[DEPRECATED]Steady Shot' WHERE `ID` = 14007;
UPDATE `quest_template` SET `LogTitle` = '[DEPRECATED]Primal Strike' WHERE `ID` = 25143;

DELETE FROM `disables` WHERE `sourceType` = 1 AND `entry` IN (570, 571, 572, 573, 14007, 25143);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(1, 570, 0, '', '', 'Deprecated quest: Mok''thardin''s Enchantment'),
(1, 571, 0, '', '', 'Deprecated quest: Mok''thardin''s Enchantment'),
(1, 572, 0, '', '', 'Deprecated quest: Mok''thardin''s Enchantment'),
(1, 573, 0, '', '', 'Deprecated quest: Mok''thardin''s Enchantment'),
(1, 14007, 0, '', '', 'Deprecated quest: Steady Shot'),
(1, 25143, 0, '', '', 'Deprecated quest: Primal Strike');

-- Fix "The Holy Water of Clarity", two quests depending on if you've quested up north or not
UPDATE `quest_template_addon` SET `PrevQuestID` = 26404, `ExclusiveGroup` = 26433 WHERE `ID` = 26433;
UPDATE `quest_template_addon` SET `ExclusiveGroup` = 26433 WHERE `ID` = 26590;
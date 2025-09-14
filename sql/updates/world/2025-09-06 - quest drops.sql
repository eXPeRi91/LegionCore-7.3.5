-- Fix loot chance for the following quest items:
--
-- Set the following to 100%:
-- 2828 = Nissa's Remains
-- 2829 = Gregor's Remains
-- 2830 = Thurman's Remains
-- 3635 = Maggot Eye's Paw
-- 4859 = Burning Blade Medallion
-- 5063 = Kreenig Snarlsnout's Tusk
-- 5089 = Console Key
-- 5544 = Bloodclaw's Collection
-- 18962 = Stinglasher's Glands
-- 33420 = Plagued Proto-Whelp Specimen
-- 34027 = Eyes of the Eagle
-- 34035 = Rotgill's Trident
-- 34387 = Barrel of Blasting Powder
-- 34621 = Claw of Claximus
-- 36753 = Tivax's Key Fragment
-- 36793 = Sarathstra's Frozen Heart
-- 36853 = Grom'thar's Head
-- 37565 = The Head of the High General
-- 39318 = Key of Warlord Zol'Maz
-- 46147 = Kaldorei Assassin's Head
-- 46365 = Mystlash Hydra Blubber
-- 46381 = Searing Roc Plumage
-- 46834 = Glomp's Booty
-- 56139 = Longhorn's Horn
-- 60874 = Deathless Sinew
-- 60876 = Walden's Elixirs
-- 62911 = Scoop of Silithid Goo
-- 62924 = Trapper Net
-- 63035 = Twilight's Hammer Armor
-- 130255 = Latara's Bow
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (2828, 2829, 2830, 3635, 4859, 5063, 5089, 5544, 18962, 33420, 34027, 34035, 34387, 34621, 36753, 36793, 36853, 37565, 39318, 46147, 46365, 46381, 46834, 56139, 60874, 60876, 62911, 62924, 63035, 130255);
--
-- Set the following to 90%:
-- 3162 = Notched Rib
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -90 WHERE `item` = 3162;
--
-- Set the following to 80%:
-- 3163 = Blackened Skull
-- 9237 = Woodpaw Gnoll Mane
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -80 WHERE `item` IN (3163, 9237);
--
-- Set the following to 50%:
-- 2834 = Embalming Ichor
-- 46392 = Venison Steak
-- 52270 = Plagued Bruin Hide
-- 54821 = Pirate's Crowbar
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -50 WHERE `item` IN (2834, 46392, 52270, 54821);


-- Following items also require cleanup of existing rows:
--
-- 4905 = Sarkoth's Mangled Claw
DELETE FROM `creature_loot_template` WHERE `item` = 4905 AND NOT `entry` = 3281;
--
-- 33284 = Gjalerbron Cage Key
DELETE FROM `creature_loot_template` WHERE `item` = 33284 AND NOT `entry` IN (23989, 23990, 23991);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -33 WHERE `item` = 33284;
--
-- 34908 = Scourge Cage Key
DELETE FROM `creature_loot_template` WHERE `item` = 34908 AND NOT `entry` IN (25609, 25611);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -50 WHERE `item` = 34908;
--
-- 34600 = Urmgrgl's Key
DELETE FROM `creature_loot_template` WHERE `item` = 34600 AND NOT `entry` = 25210;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 34600;
--
-- 34617 = Glrggl's Head
DELETE FROM `creature_loot_template` WHERE `item` = 34617 AND NOT `entry` = 25203;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 34617;
--
-- 35800 = Wind Trader Mu'fah's Remains
DELETE FROM `creature_loot_template` WHERE `item` = 35800 AND NOT `entry` = 26496;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 35800;
--
-- 35801 = The Scales of Goramosh
DELETE FROM `creature_loot_template` WHERE `item` = 35801 AND NOT `entry` = 26349;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 35801;
--
-- 36741 = Head of High Cultist Zangus
DELETE FROM `creature_loot_template` WHERE `item` = 36741 AND NOT `entry` = 26655;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36741;
--
-- 36751 = Ley Line Focus Control Ring
DELETE FROM `creature_loot_template` WHERE `item` = 36751 AND NOT `entry` = 26762;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36751;
--
-- 36752 = Anok'ra's Key Fragment
DELETE FROM `creature_loot_template` WHERE `item` = 36752 AND NOT `entry` = 26769;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36752;
--
-- 36754 = Sinok's Key Fragment
DELETE FROM `creature_loot_template` WHERE `item` = 36754 AND NOT `entry` = 26771;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36754;
--
-- 36779 = Ley Line Focus Control Amulet
DELETE FROM `creature_loot_template` WHERE `item` = 36779 AND NOT `entry` = 26815;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36779;
--
-- 36857 = Durar's Power Cell (ACore has this at 67%, blizz-like is NOT 100% but we don't care for this one as it is a single man drop)
DELETE FROM `creature_loot_template` WHERE `item` = 36857 AND NOT `entry` = 26409;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36857;
--
-- 36858 = Kathorn's Power Cell (ACore has this at 65%, blizz-like is NOT 100% but we don't care for this one as it is a single man drop)
DELETE FROM `creature_loot_template` WHERE `item` = 36858 AND NOT `entry` = 26410;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 36858;
--
-- 37305 = Captain Shely's Rutters
DELETE FROM `creature_loot_template` WHERE `item` = 37305 AND NOT `entry` = 27232;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 37305;
--
-- 37350 = Bishop Street's Prayer Book
DELETE FROM `creature_loot_template` WHERE `item` = 37350 AND NOT `entry` = 27246;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 37350;
--
-- 38098 = Dragonflayer Patriarch's Blood
DELETE FROM `creature_loot_template` WHERE `item` = 38098 AND NOT `entry` = 27926;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 38098;
--
-- 52077 = Urgent Scarlet Memorandum
DELETE FROM `creature_loot_template` WHERE `item` = 52077 AND NOT `entry` IN (1536, 1537, 1662);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -80 WHERE `item` = 52077;
--
-- 129921 = Scales of Serpentrix
DELETE FROM `creature_loot_template` WHERE `item` = 129921 AND NOT `entry` = 91808;


-- Following items require current rows to be deleted and new ones inserted because new ones are needed:
--
-- 2859 = Vile Fin Scale
DELETE FROM `creature_loot_template` WHERE `item` = 2859;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`) VALUES
(1541, 2859, -80, 0, 0, 1, 1, 0),
(1543, 2859, -80, 0, 0, 1, 1, 0),
(1544, 2859, -80, 0, 0, 1, 1, 0),
(1545, 2859, -80, 0, 0, 1, 1, 0);
--
-- 5490 = Wrathtail Head
DELETE FROM `creature_loot_template` WHERE `item` = 5490;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`) VALUES
(3711, 5490, -100, 0, 0, 1, 1, 0),
(3712, 5490, -100, 0, 0, 1, 1, 0),
(3713, 5490, -100, 0, 0, 1, 1, 0),
(3715, 5490, -100, 0, 0, 1, 1, 0),
(3717, 5490, -100, 0, 0, 1, 1, 0),
(3944, 5490, -100, 0, 0, 1, 1, 0);
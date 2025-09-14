-- Fix battle pets that should not be green to you:
-- 61143 = Mouse
-- 61258 = Rat Snake
-- 61321 = Lizard Hatchling
-- 61366 = Rat
-- 61829 = Bat
-- 62120 = Rabid Nut Varmint 5000
-- 62184 = Rock Viper
-- 62315 = Tainted Moth
-- 62895 = Oasis Moth
-- 62904 = Yellow-Bellied Marmot
-- 65124 = Luyu Moth
-- 68806 = Lofty Libram
-- 303790 = Westfall Chicken
-- 327910 = Spring Rabbit
UPDATE `creature_template` SET `faction` = 188 WHERE `entry` IN (61143, 61258, 61321, 61366, 61829, 62120, 62184, 62315, 62895, 62904, 65124, 68806, 303790, 327910);


-- Remove duplicated NPCs:
-- 6582 = Clutchmother Zavas
-- 6929 = Innkeeper Gryshka
-- 14661 = Stinglasher
-- 18297 = Gankly Rottenfist
-- 27237 = Commander Jordan
-- 30372 = Elder Whurain
-- 30373 = Elder Skywarden
-- 38305 = Gorishi Fledling Colossus
-- 38708 = Devilsaur Queen
-- 47687 = Winna's Kitten
-- 91904 = Dread-Captain Tattersail
-- 92566 = Dread-Rider Cullen
-- 92963 = Starlys Strongbow
-- 92966 = Trelan Shieldbreaker
-- 92971 = Kester Farseeker
-- 93031 = Lieutenant Desdel Stareye
-- 93234 = Ashildir
-- 94227 = Lady Sylvanas Windrunner
-- 94974 = Sirius Ebonwing
-- 94975 = Asha Ravensong
-- 95395 = Thaon Moonclaw
-- 95396 = Thaon Moonclaw
-- 96997 = Kethrazor
-- 97250 = Forsaken Bat-Rider
-- 97266 = Wrath of Dargrul
-- 97270 = Shieldmaiden Iounn
-- 97978 = Archmage Khadgar
-- 101077 = Sekhan
-- 103570 = Mardranel Forestheart
-- 110944 = Guardian Thor'el
DELETE FROM `creature` WHERE `guid` = 176480 AND `id` = 6582;
DELETE FROM `creature` WHERE `guid` IN (350650, 351133) AND `id` = 6929;
DELETE FROM `creature` WHERE `guid` IN (250636, 250637) AND `id` = 14661;
DELETE FROM `creature` WHERE `guid` = 37047 AND `id` = 18297;
DELETE FROM `creature` WHERE `guid` = 50109 AND `id` = 27237;
DELETE FROM `creature` WHERE `guid` = 188916 AND `id` = 30372;
DELETE FROM `creature` WHERE `guid` = 188924 AND `id` = 30373;
DELETE FROM `creature` WHERE `guid` = 177836 AND `id` = 38305;
DELETE FROM `creature` WHERE `guid` = 261082 AND `id` = 38708;
DELETE FROM `creature` WHERE `guid` = 172651 AND `id` = 47687;
DELETE FROM `creature` WHERE `guid` = 341176 AND `id` = 91904;
DELETE FROM `creature` WHERE `guid` = 341175 AND `id` = 92566;
DELETE FROM `creature` WHERE `guid` IN (296382, 296528) AND `id` = 92963;
DELETE FROM `creature` WHERE `guid` IN (296433, 296509) AND `id` = 92966;
DELETE FROM `creature` WHERE `guid` = 296514 AND `id` = 92971;
DELETE FROM `creature` WHERE `guid` IN (285975, 296525) AND `id` = 93031;
DELETE FROM `creature` WHERE `guid` = 341220 AND `id` = 93234;
DELETE FROM `creature` WHERE `guid` = 341179 AND `id` = 94227;
DELETE FROM `creature` WHERE `guid` = 288395 AND `id` = 94974;
DELETE FROM `creature` WHERE `guid` IN (286833, 296517) AND `id` = 94975;
DELETE FROM `creature` WHERE `guid` = 296033 AND `id` = 95395;
DELETE FROM `creature` WHERE `guid` = 11718807 AND `id` = 95396;
DELETE FROM `creature` WHERE `guid` = 366442 AND `id` = 96997;
DELETE FROM `creature` WHERE `guid` = 341178 AND `id` = 97250;
DELETE FROM `creature` WHERE `guid` = 340672 AND `id` = 97266;
DELETE FROM `creature` WHERE `guid` = 341219 AND `id` = 97270;
DELETE FROM `creature` WHERE `guid` = 369016 AND `id` = 97978;
DELETE FROM `creature` WHERE `guid` = 284250 AND `id` = 101077;
DELETE FROM `creature` WHERE `guid` = 383572 AND `id` = 103570;
DELETE FROM `creature` WHERE `guid` = 278378 AND `id` = 110944;
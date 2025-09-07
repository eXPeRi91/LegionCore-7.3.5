-- Fix NPCs that incorrectly aggressively attack the player
-- 9119 = Muigin
-- 34283 = Sabina Pilgrim
-- 46006 = Ginny Goodwin
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` IN (9119, 34283, 46006);


-- Fix NPCs that you should not be able to attack
-- 53544 = Squrky
-- 101146 = Orgrimmar Grunt
UPDATE `creature_template` SET `unit_flags` = 33536, `flags_extra` = 2 WHERE `entry` = 53544;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 101146;


-- Fix creatures in Tirisfal Glades, incorrect min/max levels
-- 1502 = Wretched Ghoul
-- 1504 = Young Night Web Spider
-- 1505 = Night Web Spider
-- 1508 = Young Scavenger
-- 1509 = Ragged Scavenger
-- 1548 = Cursed Darkhound
-- 1890 = Rattlecage Skeleton
-- 1910 = Muad
-- 38980 = Spirit of Devlin Agamand
-- 38981 = Shadow of Agamand
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (1502, 1504, 1505, 1508, 1509, 1548, 1890, 1910, 38980, 38981);


-- Fix creatures in Northern Barrens, incorrect min/max levels
-- 3243 = Savannah Highmane
-- 3268 = Razormane Thornweaver
-- 3270 = Elder Mystic Razorsnout
-- 3384 = Southsea Privateer
-- 3394 = Barak Kodobane
-- 3395 = Verog the Dervish
-- 3398 = Gesharahan
-- 3438 = Kreenig Snarlsnout
-- 3470 = Rathorian
-- 3475 = Echeyakee
-- 4166 = Gazelle
-- 5629 = Theramore Commando
-- 5828 = Humar the Pridelord
-- 5841 = Rocklance
-- 8307 = Tarban Hearthgrain
-- 9456 = Warlord Krom'zar
-- 9457 = Horde Defender
-- 9458 = Horde Axe Thrower
-- 9524 = Kolkar Invader
-- 9990 = Lanti'gah
-- 34284 = Dorak
-- 34432 = Far Watch Caravan Kodo
-- 34577 = Head Caravan Kodo
-- 34594 = Burning Blade Raider
-- 34635 = Kurak
-- 34747 = Glomp
-- 34750 = Cap'n Garvey
-- 34752 = Lieutenant Pyre
-- 34753 = Lieutenant Buckland
-- 34782 = Alicia Cuthbert
-- 34804 = Chef Toofus
-- 34829 = King Reaperclaw
-- 34846 = Wyneth
-- 44164 = Sunscale Ravager
-- 44165 = Sunscale Consort
-- 44168 = Southsea Recruit
-- 52165 = Sludge Beast
-- 52312 = Xelnaz
-- 52386 = Burning Blade Windrider
UPDATE `creature_template` SET `minlevel` = 10, `maxlevel` = 10, `ScaleLevelMin` = 10, `ScaleLevelMax` = 60 WHERE `entry` IN (3243, 3268, 3270, 3384, 3394, 3395, 3398, 3438, 3470, 3475, 4166, 5629, 5828, 5841, 8307, 9456, 9457, 9458, 9524, 9990, 34284, 34432, 34577, 34594, 34635, 34747, 34750, 34752, 34753, 34782, 34804, 34829, 34846, 44164, 44165, 44168, 52165, 52312, 52386);


-- Fix creatures in Ashenvale, incorrect min/max levels
-- 3712 = Wrathtail Razortail
-- 3736 = Darkslayer Mordenthal
-- 3749 = Foulweald Ursa
-- 3750 = Foulweald Totemic
-- 3987 = Dal Bloodclaw
-- 10641 = Branch Snapper
-- 12678 = Ursangous
-- 12860 = Duriel Moonfire
-- 12864 = Warsong Outrider
-- 12918 = Chief Murgut
-- 12921 = Enraged Foulweald
-- 25863 = Twilight Firesworn
-- 25866 = Twilight Flameguard
-- 33302 = Captain Elendilad
-- 33458 = Ashenvale Stalker
-- 34160 = Watch Wind Rider
-- 34163 = Hellscream's Hellion
-- 34204 = Protector Arminon
-- 34206 = Kaldorei Assassin
-- 34208 = Protector Endolar
-- 34283 = Sabina Pilgrim
-- 34603 = Ashenvale Assassin
-- 34609 = Demonic Invader
-- 34618 = Ota Wen
-- 44414 = Durak
UPDATE `creature_template` SET `minlevel` = 15, `maxlevel` = 15, `ScaleLevelMin` = 15, `ScaleLevelMax` = 60 WHERE `entry` IN (3712, 3736, 3749, 3750, 3987, 10641, 12678, 12860, 12864, 12918, 12921, 25863, 25866, 33302, 33458, 34160, 34163, 34204, 34206, 34208, 34283, 34603, 34609, 34618, 44414);


-- Fix creatures in Stonetalon Mountains, incorrect min/max levels
-- 38384 = Kona Thunderwalk
-- 41311 = Master Assassin Kel'istra
-- 42015 = Gnomish Bomber
UPDATE `creature_template` SET `minlevel` = 20, `maxlevel` = 20, `ScaleLevelMin` = 20, `ScaleLevelMax` = 60 WHERE `entry` IN (38384, 41311, 42015);


-- Fix creatures in Southern Barrens, incorrect min/max levels
-- 3252 = Silithid Swarmer
-- 5863 = Geopriest Gukk'rok
-- 6132 = Razorfen Servitor
-- 37513 = Sabersnout
-- 37753 = Nightmare Mass
UPDATE `creature_template` SET `minlevel` = 25, `maxlevel` = 25, `ScaleLevelMin` = 25, `ScaleLevelMax` = 60 WHERE `entry` IN (3252, 5863, 6132, 37513, 37753);


-- Fix creatures in Dustwallow Marsh, incorrect min/max levels
-- 4339 = Brimgore
-- 4841 = Deadmire
-- 14232 = Dart
-- 23786 = Stonemaul Spirit
-- 23789 = Smolderwing
-- 23864 = Zelfrax
-- 23928 = Lurking Shark
-- 23941 = Gavis Greyshield
-- 38006 = Crown Hoodlum
UPDATE `creature_template` SET `minlevel` = 35, `maxlevel` = 35, `ScaleLevelMin` = 35, `ScaleLevelMax` = 60 WHERE `entry` IN (4339, 4841, 14232, 23786, 23789, 23864, 23928, 23941, 38006);


-- Fix creatures in Western Plaguelands, incorrect min/max levels
-- 1848 = Lord Maldazzar
-- 10927 = Disturbed Resident
-- 44445 = Krastinovian Disciple
-- 45154 = Redpine Necromancer
-- 45155 = Moldfang
-- 45156 = Shadril
-- 45209 = Forsaken Outrider
-- 45212 = Gory
-- 45243 = Forsaken Trooper
UPDATE `creature_template` SET `minlevel` = 35, `maxlevel` = 35, `ScaleLevelMin` = 35, `ScaleLevelMax` = 60 WHERE `entry` IN (1848, 10927, 44445, 45154, 45155, 45156, 45209, 45212, 45243);


-- Fix creatures in Eastern Plaguelands, incorrect min/max levels
-- 8562 = Mossflayer Cannibal
-- 10699 = Carrion Scarab
-- 10822 = Warlord Thresh'jinn
-- 10823 = Zul'Brin Warpbranch
-- 10826 = Lord Darkscythe
-- 12261 = Infected Mossflayer
-- 45450 = The Lone Hunter
-- 45579 = Mossflayer Rogue
-- 45698 = Argent Warden
-- 45707 = Lord Raymond George
-- 45744 = Ix'lar the Underlord
-- 46092 = Scarlet Commander Marjhan
-- 46093 = Mataus the Wrathcaster
-- 46094 = Huntsman Leopold
-- 46095 = Rohan the Assassin
-- 46096 = Crusader Lord Valdelmar
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (8562, 10699, 10822, 10823, 10826, 12261, 45450, 45579, 45698, 45707, 45744, 46092, 46093, 46094, 46095, 46096);


-- Fix creatures in Silithus, incorrect min/max levels
-- 11735 = Stonelash Scorpid
-- 11738 = Sand Skitterer
-- 11740 = Dredge Striker
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (11735, 11738, 11740);


-- Fix creatures in Swamp of Sorrows, incorrect min/max levels
-- 5269 = Atal'ai Priest
-- 45967 = Marshfin Murkdweller
-- 46424 = Priestess Udum'bra
-- 46869 = Marshtide Invader
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (5269, 45967, 46424, 46869);


-- Fix creatures in Thousand Needles, incorrect min/max levels
-- 14426 = Harb Foulmountain
-- 40958 = Tony Two-Tusk
-- 41334 = Whrrrl
-- 45387 = Isha Gloomaxe
-- 45410 = Elder Stormhoof
-- 47503 = Heartrazor
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (14426, 40958, 41334, 45387, 45410, 47503);


-- Fix creatures in Un'Goro Crater, incorrect min/max levels
-- 6499 = Ironhide Devilsaur
-- 6556 = Muculent Ooze
-- 6581 = Ravasaur Matriarch
-- 6582 = Clutchmother Zavas
-- 9683 = Lar'korwi Mate
-- 9684 = Lar'korwi
-- 28601 = High Cultist Herenn
-- 34158 = Young Venomhide Ravasaur
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (6499, 6556, 6581, 6582, 9683, 9684, 28601, 34158);


-- Fix creatures in Hellfire Peninsula, incorrect min/max levels
-- 16939 = Void Baron Galaxis
-- 16994 = Draenei Anchorite
-- 16996 = Draenei Vindicator
-- 18978 = Heckling Fel Sprite
-- 18981 = Doomwhisperer
-- 19443 = Tagar Spinebreaker
-- 19599 = Void Servant
-- 19862 = Urtrak
-- 20145 = Unstable Voidwalker
-- 20798 = Razorsaw
UPDATE `creature_template` SET `minlevel` = 58, `maxlevel` = 58, `ScaleLevelMin` = 58, `ScaleLevelMax` = 80 WHERE `entry` IN (16939, 16994, 16996, 18978, 18981, 19443, 19599, 19862, 20145, 20798);


-- Fix creatures in Zangarmarsh, incorrect min/max levels
-- 18044 = Rajis Fyashe
-- 18089 = Bloodscale Slavedriver
-- 18121 = Ango'rosh Souleater
-- 18159 = Boss Grog'ak
-- 18160 = Overlord Gorefist
-- 18185 = Feralfen Serpent Spirit
-- 18283 = Blacksting
-- 18285 = "Count" Ungula
-- 18992 = Captain Krosh
-- 19733 = Daggerfen Servant
-- 20477 = Terrorclaw
-- 20792 = Bloodscale Elemental
-- 21894 = Xeleth
UPDATE `creature_template` SET `minlevel` = 60, `maxlevel` = 60, `ScaleLevelMin` = 60, `ScaleLevelMax` = 80 WHERE `entry` IN (18044, 18089, 18121, 18159, 18160, 18185, 18283, 18285, 18992, 19733, 20477, 20792, 21894);


-- Fix creatures in Terokkar Forest, incorrect min/max levels
--
-- 18260 = Boulderfist Invader
-- 18262 = Unkor the Ruthless
-- 18647 = Deathskitter
-- 18707 = Torgos
-- 20682 = Terokkarantula
-- 21723 = Blackwind Sabercat
-- 22038 = Hal'shulud
-- 22143 = Gordunni Back-Breaker
-- 22144 = Gordunni Elementalist
-- 22148 = Gordunni Head-Splitter
-- 22199 = Slaag
-- 22337 = Malevolent Hatchling
-- 22375 = Avatar of Terokk
-- 22376 = Minion of Terokk
-- 22387 = Lithic Oracle
-- 22388 = Lithic Talonguard
-- 22441 = Teribus the Cursed
-- 22452 = Reanimated Exarch
-- 22482 = Mature Bone Sifter
UPDATE `creature_template` SET `minlevel` = 62, `maxlevel` = 62, `ScaleLevelMin` = 62, `ScaleLevelMax` = 80 WHERE `entry` IN (18260, 18262, 18647, 18707, 20682, 21723, 22038, 22143, 22144, 22148, 22199, 22337, 22375, 22376, 22387, 22388, 22441, 22452, 22482);
-- Fix creatures in Teldrassil, incorrect min/max levels
-- 14430 = Duskstalker
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` = 14430;


-- Fix creatures in Eversong Woods, incorrect min/max levels
-- 16855 = Tregla
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` = 16855;


-- Fix creatures in The Wandering Isle, incorrect min/max levels
-- 55634 = Ruk-Ruk
-- 55640 = Thornbranch Scamp
-- 56274 = Guardian of the Elders
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (55634, 55640, 56274);


-- Fix creatures in The Lost Isles, incorrect min/max levels (have to guess on the level range, taking into account heirlooms)
-- 33420 = Strange Tentacle
-- 35650 = Sassy Hardwrench
-- 35812 = Smart Mining Monkey
-- 35882 = Orc Survivor
-- 36092 = SI: 7 Assassin
-- 36112 = Scout Brax
-- 36129 = Gyrochoppa Pilot
-- 36149 = Alliance Sailor
-- 36153 = Alliance Captain
-- 36179 = Goblin Survivor
-- 36180 = Ace
-- 36184 = Izzy
-- 36186 = Gobber
-- 36344 = Frightened Miner
-- 36404 = Candy Cane
-- 36417 = Kilag Gorefang
-- 36427 = Brett "Coins" McQuid
-- 36430 = Sally "Salvager" Sandscrew
-- 36432 = Chawg
-- 36469 = Chip Endale
-- 36615 = Doc Zapnozzle
-- 36732 = Ancient Island Turtle
-- 36740 = Teraptor Hatchling
-- 38224 = Mechachicken
-- 38359 = Vashj'elan Warrior
-- 38360 = Vashj'elan Siren
-- 38432 = Megs Dreadshredder
-- 38531 = Oomlot Warrior
-- 38574 = Oomlot Shaman
-- 38575 = Oomlot Tribesman
-- 38643 = Goblin Captive
-- 38738 = Coach Crosscheck
-- 38745 = Kezan Citizen
-- 38753 = Goblin Zombie
-- 38808 = Gaahl
-- 38809 = Malmo
-- 38810 = Teloch
-- 38811 = Oostan Headhunter
-- 38845 = Child of Volcanoth
-- 38850 = Volcanoth Champion
-- 39044 = Orc Battlesworn
-- 39068 = Orc Scout
-- 39141 = Commander Arrington
-- 39142 = Darkblade Cyn
-- 39143 = Alexi Silenthowl
-- 39193 = Brute Overseer
-- 39194 = Blastshadow the Brutemaster
-- 39195 = Delicia Whipsnaps
-- 39449 = Southsea Mercenary
-- 40064 = Jungle Panther
-- 42473 = Grimy Greasefingers
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (33420, 35650, 35812, 35882, 36092, 36112, 36129, 36149, 36153, 36179, 36180, 36184, 36186, 36344, 36404, 36417, 36427, 36430, 36432, 36469, 36615, 36732, 36740, 38224, 38359, 38360, 38432, 38531, 38574, 38575, 38643, 38738, 38745, 38753, 38808, 38809, 38810, 38811, 38845, 38850, 39044, 39068, 39141, 39142, 39143, 39193, 39194, 39195, 39449, 40064, 42473);


-- Fix creatures in Durotar, incorrect min/max levels
-- 3101 = Vile Familiar
-- 3102 = Felstalker
-- 3183 = Yarrog Baneshadow
-- 3281 = Sarkoth
-- 23543 = Shade of the Horseman
-- 35750 = Burning Blade Cultist
-- 39351 = Ghislania
-- 39352 = Gaur Icehorn
-- 39353 = Griswold Hanniston
-- 42504 = Mature Swine
-- 42594 = Orgrimmar Thief
-- 42859 = Wild Mature Swine
-- 43331 = Golden Stonefish
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (3101, 3102, 3183, 3281, 23543, 35750, 39351, 39352, 39353, 42504, 42594, 42859, 43331);


-- Fix creatures in Azuremyst Isle, incorrect min/max levels
-- 17186 = Deranged Owlbeast
-- 17187 = Aberrant Owlbeast
-- 17188 = Raving Owlbeast
-- 17448 = Chieftain Oomooroo
-- 17612 = Quel'dorei Magewraith
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (17186, 17187, 17188, 17448, 17612);


-- Fix creatures in Mulgore, incorrect min/max levels
-- 36827 = Grimtotem Vagabond
-- 36828 = Grimtotem Defiler
UPDATE `creature_template` SET `minlevel` = 1, `maxlevel` = 1, `ScaleLevelMin` = 1, `ScaleLevelMax` = 20 WHERE `entry` IN (36827, 36828);


-- Fix creatures in Bloodmyst Isle, incorrect min/max levels
-- 17715 = Atoph the Bloodcursed
UPDATE `creature_template` SET `minlevel` = 10, `maxlevel` = 10, `ScaleLevelMin` = 10, `ScaleLevelMax` = 60 WHERE `entry` = 17715;


-- Fix creatures in Ghostlands, incorrect min/max levels
-- 16292 = Aquantion
-- 16331 = Darnassian Druid
UPDATE `creature_template` SET `minlevel` = 10, `maxlevel` = 10, `ScaleLevelMin` = 10, `ScaleLevelMax` = 60 WHERE `entry` IN (16292, 16331);


-- Fix creatures in Darkshore, incorrect min/max levels
-- 2191 = Licillin
-- 2192 = Firecaller Radison
-- 7016 = Lady Vespira
-- 32858 = Shatterspear Champion
-- 32862 = Jor'kil the Soulripper
-- 34398 = Nightmare Guardian
-- 34399 = Nightmare Spawn
UPDATE `creature_template` SET `minlevel` = 10, `maxlevel` = 10, `ScaleLevelMin` = 10, `ScaleLevelMax` = 60 WHERE `entry` IN (2191, 2192, 7016, 32858, 32862, 34398, 34399);


-- Fix creatures in Westfall, incorrect min/max levels
-- 573 = Foe Reaper 4000
-- 1424 = Master Digger
UPDATE `creature_template` SET `minlevel` = 10, `maxlevel` = 10, `ScaleLevelMin` = 10, `ScaleLevelMax` = 60 WHERE `entry` IN (573, 1424);


-- Fix creatures in Hillsbrad Foothills, incorrect min/max levels
-- 2319 = Syndicate Wizard
-- 2473 = Granistad
-- 2474 = Kurdros
-- 14221 = Gravis Slipknot
-- 14222 = Araga
-- 14275 = Tamra Stormpike
-- 14276 = Scargil
-- 14278 = Ro'Bark
-- 47433 = Captured Bloodfang Worgen
-- 48187 = Hill Fawn
-- 48482 = Stormpike Mountaineer
-- 48483 = Stormpike Ram Rider
-- 48484 = Bloodfang Sentry
UPDATE `creature_template` SET `minlevel` = 15, `maxlevel` = 15, `ScaleLevelMin` = 15, `ScaleLevelMax` = 60 WHERE `entry` IN (2319, 2473, 2474, 14221, 14222, 14275, 14276, 14278, 47433, 48187, 48482, 48483, 48484);


-- Fix creatures in Wailing Caverns, incorrect min/max levels
-- 3636 = Deviate Ravager
-- 3637 = Deviate Guardian
-- 3640 = Evolving Ectoplasm
-- 3653 = Kresh
-- 3654 = Mutanus the Devourer
-- 3669 = Lord Cobrahn
-- 3670 = Lord Pythas
-- 3671 = Lady Anacondra
-- 3673 = Lord Serpentis
-- 3674 = Skum
-- 3678 = Muyoh
-- 3840 = Druid of the Fang
-- 5048 = Deviate Adder
-- 5053 = Deviate Crocolisk
-- 5055 = Deviate Lasher
-- 5056 = Deviate Dreadfang
-- 5755 = Deviate Viper
-- 5756 = Deviate Venomwing
-- 5761 = Deviate Shambler
-- 5767 = Nalpak
-- 5768 = Ebru
-- 5775 = Verdan the Everliving
-- 5912 = Deviate Faerie Dragon
-- 8886 = Deviate Python
UPDATE `creature_template` SET `minlevel` = 17, `maxlevel` = 17, `ScaleLevelMin` = 17, `ScaleLevelMax` = 60 WHERE `entry` IN (3636, 3637, 3640, 3653, 3654, 3669, 3670, 3671, 3673, 3674, 3678, 3840, 5048, 5053, 5055, 5056, 5755, 5756, 5761, 5767, 5768, 5775, 5912, 8886);


-- Fix creatures in Shadowfang Keep, incorrect min/max levels
-- 3865 = Shadow Charger
-- 3872 = Deathsworn Captain
-- 47027 = Bloodfang Berserker
UPDATE `creature_template` SET `minlevel` = 17, `maxlevel` = 17, `ScaleLevelMin` = 17, `ScaleLevelMax` = 60 WHERE `entry` IN (3865, 3872, 47027);


-- Fix creatures in Arathi Highlands, incorrect min/max levels
-- 2595 = Daggerspine Raider
-- 2596 = Daggerspine Sorceress
-- 2755 = Myzrael
-- 2755 = Myzrael
-- 2776 = Vengeful Surge
-- 2793 = Kor'gresh Coldrage
UPDATE `creature_template` SET `minlevel` = 25, `maxlevel` = 25, `ScaleLevelMin` = 25, `ScaleLevelMax` = 60 WHERE `entry` IN (2595, 2596, 2755, 2755, 2776, 2793);


-- Fix creatures in Northern Stranglethorn, incorrect min/max levels
-- 676 = Venture Co. Surveyor
-- 1511 = Enraged Silverback Gorilla
-- 1516 = Konda
-- 51662 = Mahamba
UPDATE `creature_template` SET `minlevel` = 25, `maxlevel` = 25, `ScaleLevelMin` = 25, `ScaleLevelMax` = 60 WHERE `entry` IN (676, 1511, 1516, 51662);


-- Fix creatures in The Cape of Stranglethorn, incorrect min/max levels
-- 1514 = Mokk the Savage
-- 43110 = Gurubashi Arena Challenger
-- 43542 = Lime Thief
UPDATE `creature_template` SET `minlevel` = 30, `maxlevel` = 30, `ScaleLevelMin` = 30, `ScaleLevelMax` = 60 WHERE `entry` IN (1514, 43110, 43542);


-- Fix creatures in The Hinterlands, incorrect min/max levels
-- 8212 = The Reak
-- 14748 = Vilebranch Kidnapper
-- 42877 = Morta'gya the Keeper
-- 42879 = Spawn of Shadra
-- 43541 = Deathstalker Invader
UPDATE `creature_template` SET `minlevel` = 30, `maxlevel` = 30, `ScaleLevelMin` = 30, `ScaleLevelMax` = 60 WHERE `entry` IN (8212, 14748, 42877, 42879, 43541);


-- Fix creatures in Desolace, incorrect min/max levels
-- 4667 = Burning Blade Shadowmage
-- 11521 = Kodo Apparition
-- 11521 = Kodo Apparition
-- 11560 = Magrami Spectre
-- 14226 = Kaskk
-- 35454 = Doomguard Invader
-- 35647 = Nazargen
-- 35750 = Snapjaw Basilisk
-- 35811 = Famished Bonepaw
-- 36159 = Magram Defender
-- 36353 = Brendol
-- 36414 = Burning Blade Warlock
-- 36441 = Doomguard Defender
-- 36442 = Agogridon
-- 37703 = Surging Elemental
-- 39852 = Raging Fire Elemental
UPDATE `creature_template` SET `minlevel` = 30, `maxlevel` = 30, `ScaleLevelMin` = 30, `ScaleLevelMax` = 60 WHERE `entry` IN (4667, 11521, 11521, 11560, 14226, 35454, 35647, 35750, 35811, 36159, 36353, 36414, 36441, 36442, 37703, 39852);


-- Fix creatures in Maraudon - Earth Song Falls, incorrect min/max levels
-- 11783 = Theradrim Shardling
-- 11784 = Theradrim Guardian
-- 12201 = Princess Theradras
-- 12207 = Thessala Hydra
-- 13323 = Subterranean Diemetradon
UPDATE `creature_template` SET `minlevel` = 34, `maxlevel` = 34, `ScaleLevelMin` = 34, `ScaleLevelMax` = 60 WHERE `entry` IN (11783, 11784, 12201, 12207, 13323);


-- Fix creatures in Feralas, incorrect min/max levels
-- 4795 = Force of Nature
-- 5292 = Feral Scar Yeti
-- 5346 = Bloodroar the Stalker
-- 5349 = Arash-ethis
-- 7807 = Homing Robot OOX-22/FE
-- 8075 = Edana Hatetalon
-- 11440 = Gordok Enforcer
-- 11443 = Gordok Ogre-Mage
-- 11447 = Mushgog
-- 11497 = The Razza
-- 12418 = Gordok Hyena
-- 39607 = Glak the Quenched
-- 39608 = Stonemaul Raider
-- 39704 = Gordok Onlooker
-- 39829 = Burning Exile
-- 39830 = Glacial Exile
-- 39831 = Thundering Windfury
-- 39853 = Taerar
-- 39952 = Gordunni Hillguard
-- 39957 = Gordunni Tamer
-- 39958 = Bigfist
-- 39965 = Gordunni Channeler
-- 40059 = Highborne Poltergeist
-- 40131 = Sensiria
-- 43737 = Rumbling Betrayer
-- 43864 = Braz the Windreaver
UPDATE `creature_template` SET `minlevel` = 35, `maxlevel` = 35, `ScaleLevelMin` = 35, `ScaleLevelMax` = 60 WHERE `entry` IN (4795, 5292, 5346, 5349, 7807, 8075, 11440, 11443, 11447, 11497, 12418, 39607, 39608, 39704, 39829, 39830, 39831, 39853, 39952, 39957, 39958, 39965, 40059, 40131, 43737, 43864);


-- Fix creatures in Scholomance, incorrect min/max levels
-- 58503 = Brittle Skeleton
-- 58633 = Instructor Chillheart
-- 58722 = Lilian Voss
-- 58757 = Scholomance Acolyte
-- 58758 = Soul Fragment
-- 58822 = Risen Guard
-- 58823 = Scholomance Neophyte
-- 59080 = Darkmaster Gandling
-- 59100 = Expired Test Subject
-- 59153 = Rattlegore
-- 59184 = Jandice Barov
-- 59193 = Boneweaver
-- 59359 = Flesh Horror
-- 59368 = Krastinovian Carver
-- 59369 = Doctor Theolen Krastinov
-- 59467 = Candlestick Mage
-- 59501 = Reanimated Corpse
-- 59613 = Professor Slate
-- 59614 = Bored Student
-- 59980 = Meat Graft
UPDATE `creature_template` SET `minlevel` = 38, `maxlevel` = 38, `ScaleLevelMin` = 38, `ScaleLevelMax` = 60 WHERE `entry` IN (58503, 58633, 58722, 58757, 58758, 58822, 58823, 59080, 59100, 59153, 59184, 59193, 59359, 59368, 59369, 59467, 59501, 59613, 59614, 59980);


-- Fix creatures in Badlands, incorrect min/max levels
-- 46658 = Nyxondra
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` = 46658;


-- Fix creatures in Burning Steppes, incorrect min/max levels
-- 10119 = Volchan
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` = 10119;


-- Fix creatures in Searing Gorge, incorrect min/max levels
-- 8283 = Slave Master Blackheart
-- 47271 = Dig-Boss Dinwhisker
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (8283, 47271);


-- Fix creatures in Tanaris, incorrect min/max levels
-- 38749 = Captain Dreadbeard
-- 39075 = The Ginormus
-- 40547 = Kesley Steelspark
-- 44761 = Aquementas the Unchained
-- 44767 = Occulus the Corrupted
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (38749, 39075, 40547, 44761, 44767);


-- Fix creatures in Felwood, incorrect min/max levels
-- 7135 = Infernal Bodyguard
-- 7149 = Withered Protector
-- 9454 = Xavathras
-- 9877 = Prince Xavalis
-- 14339 = Death Howl
-- 14340 = Alshirr Banebreath
-- 14345 = The Ongar
-- 47439 = Shadowsworn Netherguard
-- 47601 = Jadefire Defender
-- 48154 = Jadefire Shifter
-- 48493 = Alton Redding
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (7135, 7149, 9454, 9877, 14339, 14340, 14345, 47439, 47601, 48154, 48493);


-- Fix creatures in Blasted Lands, incorrect min/max levels
-- 5974 = Dreadmaul Ogre
-- 5975 = Dreadmaul Ogre Mage
-- 5976 = Dreadmaul Brute
-- 6007 = Shadowsworn Enforcer
-- 6008 = Shadowsworn Warlock
-- 41267 = Spirit of Grol
-- 41386 = Bloodwash Barbarian
-- 41387 = Bloodwash Enchantress
-- 41404 = Bloodwash Gambler
UPDATE `creature_template` SET `minlevel` = 40, `maxlevel` = 40, `ScaleLevelMin` = 40, `ScaleLevelMax` = 60 WHERE `entry` IN (5974, 5975, 5976, 6007, 6008, 41267, 41386, 41387, 41404);


-- Fix creatures in Dire Maul - Gordok Commons, incorrect min/max levels
-- 11451 = Wildspawn Satyr
-- 11452 = Wildspawn Rogue
-- 11453 = Wildspawn Trickster
-- 11454 = Wildspawn Betrayer
-- 11455 = Wildspawn Felsworn
-- 11456 = Wildspawn Shadowstalker
-- 11457 = Wildspawn Hellcaller
-- 11461 = Warpwood Guardian
-- 11462 = Warpwood Treant
-- 11490 = Zevrim Thornhoof
-- 11491 = Old Ironbark
-- 11492 = Alzzin the Wildshaper
-- 13021 = Warpwood Crusher
-- 13022 = Whip Lasher
-- 13196 = Phase Lasher
-- 13197 = Fel Lash
-- 13276 = Wildspawn Imp
-- 13280 = Hydrospawn
-- 13285 = Death Lash
-- 14327 = Lethtendris
-- 14349 = Pimgib
-- 14350 = Hydroling
-- 14354 = Pusillin
-- 44969 = Furgus Warpwood
-- 44971 = "Ambassador" Dagg'thol
UPDATE `creature_template` SET `minlevel` = 42, `maxlevel` = 42, `ScaleLevelMin` = 42, `ScaleLevelMax` = 60 WHERE `entry` IN (11451, 11452, 11453, 11454, 11455, 11456, 11457, 11461, 11462, 11490, 11491, 11492, 13021, 13022, 13196, 13197, 13276, 13280, 13285, 14327, 14349, 14350, 14354, 44969, 44971);


-- Fix creatures in Stratholme - Main Gate, incorrect min/max levels
-- 10381 = Ravaged Cadaver
-- 10382 = Mangled Cadaver
-- 10383 = Broken Cadaver
-- 10384 = Spectral Citizen
-- 10385 = Ghostly Citizen
-- 10387 = Vengeful Phantom
-- 10390 = Skeletal Guardian
-- 10391 = Skeletal Berserker
-- 10405 = Plague Ghoul
-- 10414 = Patchwork Horror
-- 10418 = Risen Guardsman
-- 10419 = Risen Conjuror
-- 10420 = Risen Initiate
-- 10421 = Risen Defender
-- 10422 = Risen Sorceror
-- 10423 = Risen Priest
-- 10424 = Risen Gallant
-- 10425 = Risen Battle Mage
-- 10426 = Risen Inquisitor
-- 10516 = The Unforgiven
-- 10558 = Hearthsinger Forresten
-- 10808 = Timmy the Cruel
-- 10811 = Instructor Galford
-- 10813 = Balnazzar
-- 10997 = Willey Hopebreaker
-- 11032 = Commander Malor
-- 11043 = Risen Monk
-- 11054 = Risen Rifleman
-- 11058 = Fras Siabi
-- 11082 = Stratholme Courier
-- 11120 = Risen Hammersmith
-- 11143 = Postmaster Malown
UPDATE `creature_template` SET `minlevel` = 42, `maxlevel` = 42, `ScaleLevelMin` = 42, `ScaleLevelMax` = 60 WHERE `entry` IN (10381, 10382, 10383, 10384, 10385, 10387, 10390, 10391, 10405, 10414, 10418, 10419, 10420, 10421, 10422, 10423, 10424, 10425, 10426, 10516, 10558, 10808, 10811, 10813, 10997, 11032, 11043, 11054, 11058, 11082, 11120, 11143);


-- Fix creatures in Zul'Farrak, incorrect min/max levels
-- 5648 = Sandfury Shadowcaster
-- 5649 = Sandfury Blood Drinker
-- 5650 = Sandfury Witch Doctor
-- 7246 = Sandfury Shadowhunter
-- 7247 = Sandfury Soul Eater
-- 7267 = Chief Ukorz Sandscalp
-- 7268 = Sandfury Guardian
-- 7269 = Scarab
-- 7272 = Theka the Martyr
-- 7273 = Gahz'rilla
-- 7274 = Sandfury Executioner
-- 7275 = Shadowpriest Sezz'ziz
-- 7276 = Zul'Farrak Dead Hero
-- 7286 = Zul'Farrak Zombie
-- 7787 = Sandfury Slave
-- 7788 = Sandfury Drudge
-- 7789 = Sandfury Cretin
-- 7795 = Hydromancer Velratha
-- 7796 = Nekrum Gutchewer
-- 7797 = Ruuzlu
-- 8095 = Sul'lithuz Sandcrawler
-- 8120 = Sul'lithuz Abomination
-- 8127 = Antu'sul
-- 8876 = Sandfury Acolyte
-- 8877 = Sandfury Zealot
UPDATE `creature_template` SET `minlevel` = 44, `maxlevel` = 44, `ScaleLevelMin` = 44, `ScaleLevelMax` = 60 WHERE `entry` IN (5648, 5649, 5650, 7246, 7247, 7267, 7268, 7269, 7272, 7273, 7274, 7275, 7276, 7286, 7787, 7788, 7789, 7795, 7796, 7797, 8095, 8120, 8127, 8876, 8877);


-- Fix creatures in Stratholme - Service Entrance, incorrect min/max levels
-- 10394 = Black Guard Sentry
-- 10398 = Thuzadin Shadowcaster
-- 10399 = Thuzadin Acolyte
-- 10400 = Thuzadin Necromancer
-- 10406 = Ghoul Ravener
-- 10407 = Fleshflayer Ghoul
-- 10409 = Rockwing Screecher
-- 10412 = Crypt Crawler
-- 10413 = Crypt Beast
-- 10416 = Bile Spewer
-- 10417 = Venom Belcher
-- 10435 = Magistrate Barthilas
-- 10436 = Baroness Anastari
-- 10437 = Nerub'enkan
-- 10439 = Ramstein the Gorger
-- 10463 = Shrieking Banshee
-- 10464 = Wailing Banshee
-- 10876 = Undead Scarab
-- 11030 = Mindless Undead
-- 11121 = Black Guard Swordsmith
-- 11142 = Undead Postman
-- 42973 = Eye of Naxxramas
-- 45412 = Lord Aurius Rivendare
UPDATE `creature_template` SET `minlevel` = 46, `maxlevel` = 46, `ScaleLevelMin` = 46, `ScaleLevelMax` = 60 WHERE `entry` IN (10394, 10398, 10399, 10400, 10406, 10407, 10409, 10412, 10413, 10416, 10417, 10435, 10436, 10437, 10439, 10463, 10464, 10876, 11030, 11121, 11142, 42973, 45412);


-- Fix creatures in Sunken Temple, incorrect min/max levels
-- 5270 = Atal'ai Corpse Eater
-- 5271 = Atal'ai Deathwalker
-- 5273 = Atal'ai High Priest
-- 5277 = Nightmare Scalebane
-- 5280 = Nightmare Wyrmkin
-- 5283 = Nightmare Wanderer
-- 5291 = Hakkari Frostwing
-- 5711 = Ogom the Wretched
-- 8319 = Nightmare Whelp
-- 8336 = Hakkari Sapper
-- 8443 = Avatar of Hakkar
UPDATE `creature_template` SET `minlevel` = 50, `maxlevel` = 50, `ScaleLevelMin` = 50, `ScaleLevelMax` = 60 WHERE `entry` IN (5270, 5271, 5273, 5277, 5280, 5283, 5291, 5711, 8319, 8336, 8443);


-- Fix creatures in Plaguelands: The Scarlet Enclave, incorrect min/max levels (have to guess on the level range, taking into account heirlooms)
-- 28557 = Scarlet Peasant
-- 28577 = Citizen of Havenshire
-- 28605 = Havenshire Stallion
-- 28608 = Scarlet Medic
-- 28609 = Scarlet Infantryman
-- 28610 = Scarlet Marksman
-- 28611 = Scarlet Captain
-- 28819 = Scarlet Miner
-- 28822 = Scarlet Miner
-- 28841 = Scarlet Miner
-- 28846 = Scarlet Ghost
-- 28906 = Scourge Gryphon
-- 28936 = Scarlet Commander
-- 28939 = Scarlet Preacher
-- 28940 = Scarlet Crusader
-- 28941 = Citizen of New Avalon
-- 28942 = Citizen of New Avalon
-- 28945 = Mayor Quimby
-- 28946 = New Avalon Councilman
-- 29000 = Scarlet Commander Rodrick
-- 29007 = Crimson Acolyte
-- 29076 = Scarlet Courier
-- 29080 = Scarlet Champion
UPDATE `creature_template` SET `minlevel` = 55, `maxlevel` = 55, `ScaleLevelMin` = 55, `ScaleLevelMax` = 65 WHERE `entry` IN (28557, 28577, 28605, 28608, 28609, 28610, 28611, 28819, 28822, 28841, 28846, 28906, 28936, 28939, 28940, 28941, 28942, 28945, 28946, 29000, 29007, 29076, 29080);


-- Fix creatures in Borean Tundra, incorrect min/max levels
-- 25204 = Glimmer Bay Orca
-- 25215 = Winterfin Shorestriker
-- 25216 = Winterfin Oracle
-- 25451 = Nerub'ar Sky Darkener
-- 25844 = Northsea Thug
-- 32358 = Fumblub Gearwind
UPDATE `creature_template` SET `minlevel` = 58, `maxlevel` = 58, `ScaleLevelMin` = 58, `ScaleLevelMax` = 80 WHERE `entry` IN (25204, 25215, 25216, 25451, 25844, 32358);


-- Fix creatures in Howling Fjord, incorrect min/max levels
-- 23653 = Winterskorn Spearman
-- 23655 = Winterskorn Bonegrinder
-- 23657 = Winterskorn Skaid
-- 23983 = North Fleet Marine
-- 24238 = Bjorn Halgurdsson
-- 32398 = King Ping
UPDATE `creature_template` SET `minlevel` = 58, `maxlevel` = 58, `ScaleLevelMin` = 58, `ScaleLevelMax` = 80 WHERE `entry` IN (23653, 23655, 23657, 23983, 24238, 32398);


-- Fix creatures in Grizzly Hills, incorrect min/max levels
-- 27118 = Conquest Hold Raider
UPDATE `creature_template` SET `minlevel` = 63, `maxlevel` = 63, `ScaleLevelMin` = 63, `ScaleLevelMax` = 80 WHERE `entry` = 27118;


-- Fix creatures in Nagrand, incorrect min/max levels
-- 18043 = Agitated Orc Spirit
-- 18069 = Mogor
-- 18145 = Watoosun's Polluted Essence
-- 18182 = Gurok the Usurper
-- 18226 = Talbuk Patriarch
-- 18398 = Brokentoe
-- 18399 = Murkblood Twin
-- 18400 = Rokdar the Sundered Lord
-- 18401 = Skra'gath
-- 18402 = Warmaul Champion
-- 18423 = Cho'war the Pillager
-- 18440 = Warmaul Chef Bufferlo
-- 19055 = Windroc Matriarch
UPDATE `creature_template` SET `minlevel` = 64, `maxlevel` = 64, `ScaleLevelMin` = 64, `ScaleLevelMax` = 80 WHERE `entry` IN (18043, 18069, 18145, 18182, 18226, 18398, 18399, 18400, 18401, 18402, 18423, 18440, 19055);


-- Fix creatures in Blade's Edge Mountains, incorrect min/max levels
-- 18690 = Morcrush
-- 18692 = Hemathion
-- 18693 = Speaker Mar'grom
-- 19963 = Doomcryer
-- 20723 = Korgaah
-- 20765 = Bladespire Crusher
-- 20766 = Bladespire Mystic
-- 20768 = Gnosh Brognat
-- 21057 = Nexus-Prince Razaan
-- 21319 = Gor Grimgut
-- 21492 = Wyrmcult Blessed
-- 21514 = Gorgrom the Dragon-Eater
-- 21767 = Harbinger of the Raven
-- 21853 = Raven's Wood Ent
-- 22182 = Lightning Wasp
-- 22187 = Bladespine Basilisk
-- 22201 = Fear Whisperer
-- 22217 = Felstorm Corruptor
-- 22218 = Insidious Familiar
-- 22221 = Felstorm Overseer
-- 22275 = Apexis Guardian
-- 22281 = Galvanoth
-- 22286 = Fel Rager
-- 22287 = Amberpelt Clefthoof
-- 22289 = Darkflame Infernal
-- 22304 = Mo'arg Extractor
-- 22327 = Terror-Fire Guardian
-- 22385 = Terrordar the Tormentor
-- 22392 = Wrath Fiend
-- 22396 = Draaca Longtail
-- 22911 = Vim'gol the Vile
-- 23174 = Crystalfused Miner
-- 23386 = Gan'arg Analyzer
UPDATE `creature_template` SET `minlevel` = 65, `maxlevel` = 65, `ScaleLevelMin` = 65, `ScaleLevelMax` = 80 WHERE `entry` IN (18690, 18692, 18693, 19963, 20723, 20765, 20766, 20768, 21057, 21319, 21492, 21514, 21767, 21853, 22182, 22187, 22201, 22217, 22218, 22221, 22275, 22281, 22286, 22287, 22289, 22304, 22327, 22385, 22392, 22396, 22911, 23174, 23386);


-- Fix creatures in Scholazar Basin, incorrect min/max levels
-- 28105 = Warlord Tartek
-- 28213 = Hardknuckle Matriarch
-- 28288 = Farunn
-- 28317 = Bushwhacker
-- 28325 = Ravenous Mangal Crocolisk
-- 28358 = Venomtip
-- 28538 = Cultist Saboteur
-- 41513 = Siltslither Eel
UPDATE `creature_template` SET `minlevel` = 66, `maxlevel` = 66, `ScaleLevelMin` = 66, `ScaleLevelMax` = 80 WHERE `entry` IN (28105, 28213, 28288, 28317, 28325, 28358, 28538, 41513);


-- Fix creatures in Netherstorm, incorrect min/max levels
-- 18544 = Veraku
-- 18698 = Ever-Core the Punisher
-- 19493 = Ekkorash the Inquisitor
-- 19494 = Ar'kelos
-- 19593 = Spellbinder Maryana
-- 19635 = Captain Arathyn
-- 19653 = Glacius
-- 19657 = Summoner Kanthin
-- 19705 = Master Daellis Dawnstrike
-- 19851 = Negatron
-- 19940 = Apex
-- 20218 = Sunfury Technician
-- 20397 = Overseer Seylanna
-- 20402 = Legion Shocktrooper
-- 20403 = Legion Destroyer
-- 20404 = Warp-Gate Engineer
-- 20416 = Overseer Theredis
-- 20435 = Overseer Athanel
-- 20436 = Sunfury Protector
-- 20438 = Ara Technician
-- 20439 = Ara Engineer
-- 20480 = Kirin'Var Ghost
-- 20783 = Porfus the Gem Gorger
-- 20784 = Armbreaker Huffaz
-- 20794 = Kaylaan the Lost
-- 23008 = Ethereum Jailor
UPDATE `creature_template` SET `minlevel` = 67, `maxlevel` = 67, `ScaleLevelMin` = 67, `ScaleLevelMax` = 80 WHERE `entry` IN (18544, 18698, 19493, 19494, 19593, 19635, 19653, 19657, 19705, 19851, 19940, 20218, 20397, 20402, 20403, 20404, 20416, 20435, 20436, 20438, 20439, 20480, 20783, 20784, 20794, 23008);


-- Fix creatures in Shadowmoon Valley, incorrect min/max levels
-- 18694 = Collidus the Warp-Watcher
-- 18696 = Kraator
-- 20427 = Veneratus the Many
-- 20795 = Keeper of the Cistern
-- 21044 = Coilskar Assassin
-- 21181 = Cyrukh the Firelord
-- 21205 = Ravenous Flayer Matriarch
-- 21287 = Warbringer Razuun
-- 21753 = Shadow Council Felsworn
-- 21778 = Doctor Gutrick
-- 21779 = Doctor Maleficus
-- 21788 = Shadowmoon Zealot
-- 21801 = Vhel'kur
-- 21815 = Cleric of Karabor
-- 21960 = Gan'arg Technician
UPDATE `creature_template` SET `minlevel` = 67, `maxlevel` = 67, `ScaleLevelMin` = 67, `ScaleLevelMax` = 80 WHERE `entry` IN (18694, 18696, 20427, 20795, 21044, 21181, 21205, 21287, 21753, 21778, 21779, 21788, 21801, 21815, 21960);


-- Fix creatures in The Storm Peaks, incorrect min/max levels
-- 35189 = Skoll
UPDATE `creature_template` SET `minlevel` = 67, `maxlevel` = 67, `ScaleLevelMin` = 67, `ScaleLevelMax` = 80 WHERE `entry` = 35189;


-- Fix creatures in The Jade Forest, incorrect min/max levels
-- 51078 = Ferdinand
-- 54924 = Zhi-Zhi
-- 54925 = Husshun
-- 54926 = Xiao
-- 54930 = Greenwood Thief
-- 54944 = Tian Pupil
-- 54987 = Greenwood Trickster
-- 54988 = Waxwood Hunter
-- 55238 = Waxwood Matriarch
-- 56209 = Pandriarch Bramblestaff
-- 56210 = Pandriarch Goldendraft
-- 56401 = Greenstone Nibbler
-- 56404 = Greenstone Gorger
-- 56820 = Water Fiend
-- 57232 = Dappled Moth
-- 57237 = Bookworm
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80, `ScaleLevelMin` = 80, `ScaleLevelMax` = 90 WHERE `entry` IN (51078, 54924, 54925, 54926, 54930, 54944, 54987, 54988, 55238, 56209, 56210, 56401, 56404, 56820, 57232, 57237);


-- Fix creatures in Mount Hyjal, incorrect min/max levels
-- 7461 = Hederine Initiate
-- 7462 = Hederine Manastalker
-- 7463 = Hederine Slayer
-- 39446 = Lycanthoth
-- 39658 = Spinescale Basilisk
-- 39752 = Failed Supplicant
-- 39828 = Twilight Guard
-- 40403 = Spinescale Matriarch
-- 40409 = Gromm'ko
-- 40562 = Twilight Initiate
-- 40564 = Fiery Instructor
-- 40573 = Twilight Stormwaker
-- 40922 = Okrog
-- 41027 = Wormwing Screecher
-- 41084 = Blaithe
-- 41112 = Marion Wormwing
-- 41255 = Sethria
-- 46925 = Ashbearer
-- 46991 = Unbound Fire Elemental
-- 52816 = Charred Invader
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80, `ScaleLevelMin` = 80, `ScaleLevelMax` = 90 WHERE `entry` IN (7461, 7462, 7463, 39446, 39658, 39752, 39828, 40403, 40409, 40562, 40564, 40573, 40922, 41027, 41084, 41112, 41255, 46925, 46991, 52816);


-- Fix creatures in Krasarang Wilds, incorrect min/max levels
-- 50352 = Qu'nas
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `ScaleLevelMin` = 81, `ScaleLevelMax` = 90 WHERE `entry` = 50352;


-- Fix creatures in Frostfire Ridge, incorrect min/max levels
-- 58071 = Trained Compy
-- 70858 = Daggermaw Icegazer
-- 70898 = Thunderlord Gronnstalker
-- 71646 = Captive Gronn
-- 71647 = Thunderlord Spearhand
-- 71669 = Kur'ak the Binder
-- 71721 = Canyon Icemother
-- 72953 = Grimfrost Wolfslayer
-- 72955 = Grimfrost Drudge
-- 72987 = Grimfrost Lavaslinger
-- 73643 = Grimfrost Dunescout
-- 73700 = Slag Elemental
-- 74096 = Thunderlord Gronnbreaker
-- 74154 = Thunderlord Lasher
-- 74160 = Thunderlord Beastwrangler
-- 74614 = Kram'ak
-- 74653 = Warleader Gargrak
-- 75421 = Icebrood Pup
-- 76398 = Pack Beast
-- 76509 = Kram'akan Meltmaw
-- 76848 = Grondo
-- 76891 = Ice Spider
-- 76894 = Pale Skinslicer
-- 77100 = Iron Engineer
-- 77103 = Black Tar
-- 77147 = Iron Thunderguard
-- 77348 = Pale Tormentor
-- 78631 = Frozen Fury
-- 78700 = Thunderlord Provisioner
-- 78867 = Breathless
-- 79145 = Yaga the Scarred
-- 79146 = Bloody Tusk
-- 79147 = Severmaw
-- 80167 = Groog
-- 80192 = Icecave Bat
-- 80242 = Chillfang
-- 81398 = Frostwall Goren Hatchling
-- 86593 = Frostfire Gronnling
-- 86594 = Dominated Gronnling
UPDATE `creature_template` SET `minlevel` = 90, `maxlevel` = 90, `ScaleLevelMin` = 90, `ScaleLevelMax` = 100 WHERE `entry` IN (58071, 70858, 70898, 71646, 71647, 71669, 71721, 72953, 72955, 72987, 73643, 73700, 74096, 74154, 74160, 74614, 74653, 75421, 76398, 76509, 76848, 76891, 76894, 77100, 77103, 77147, 77348, 78631, 78700, 78867, 79145, 79146, 79147, 80167, 80192, 80242, 81398, 86593, 86594);


-- Fix creatures in Gorgrond, incorrect min/max levels
-- 75835 = Stonemaul Slaver
-- 75864 = Slavemaster Ok'mok
-- 76473 = Mother Araneae
-- 77020 = Kor'gall
-- 78819 = Iyu
-- 79621 = Slave Hunter Brol
-- 79623 = Slave Hunter Krag
-- 79626 = Slave Hunter Mol
-- 79629 = Stomper Kreego
-- 79726 = Jabberback
-- 79727 = Kigli'ak
-- 79728 = Stribit
-- 81617 = Infested Orc
-- 81631 = Botani Grovetender
-- 81634 = Voice of Iyu
-- 81676 = Lera Ashtoes
-- 81684 = Iyun Reclaimer
-- 81690 = Acidmouth Breacher
-- 81691 = Shardback Breacher
-- 81788 = Iyun Pustule
-- 81991 = Dark Iron Dwarf
-- 82311 = Char the Burning
-- 82322 = Tangleheart Cultivator
-- 82372 = Ontogen the Harvester
-- 82841 = Infested Behemoth
-- 85209 = Angered Sapling
-- 86088 = Rangari Kolaan
-- 86137 = Sunclaw
-- 86157 = Grulkor
-- 88512 = Siege Cannon
UPDATE `creature_template` SET `minlevel` = 92, `maxlevel` = 92, `ScaleLevelMin` = 92, `ScaleLevelMax` = 100 WHERE `entry` IN (75835, 75864, 76473, 77020, 78819, 79621, 79623, 79626, 79629, 79726, 79727, 79728, 81617, 81631, 81634, 81676, 81684, 81690, 81691, 81788, 81991, 82311, 82322, 82372, 82841, 85209, 86088, 86137, 86157, 88512);


-- Fix creatures in WoD: Talador, incorrect min/max levels
-- 79190 = Glowgullet Devourer
-- 79334 = No'losh
-- 80072 = Iridium Geode
-- 80081 = Albino Cave Ambusher
-- 80082 = Cave Hunter
UPDATE `creature_template` SET `minlevel` = 94, `maxlevel` = 94, `ScaleLevelMin` = 94, `ScaleLevelMax` = 100 WHERE `entry` IN (79190, 79334, 80072, 80081, 80082);


-- Fix creatures in WoD: Nagrand, incorrect min/max levels
-- 82912 = Grizzlemaw
UPDATE `creature_template` SET `minlevel` = 98, `maxlevel` = 98, `ScaleLevelMin` = 98, `ScaleLevelMax` = 100 WHERE `entry` = 82912;
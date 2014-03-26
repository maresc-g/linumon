BEGIN;

/* Inserting Users */
DELETE FROM `User`;

INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES
       (1, 'Laurent', 'yolo'),
       (2, 'Cyril', 'swag');

/* Inserting EffectLibs */
DELETE FROM `EffectLib`;

INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES
       ( 1, 'HesodeEffect',			'Libs/HesodeEffect.so'),
       ( 2, 'CelestiaEffect',			'Libs/CelestiaEffect.so'),
       ( 3, 'NormalEffect',			'Libs/NormalEffect.so'),
       ( 4, 'PotionEffect',			'Libs/PotionEffect.so'),
       ( 5, 'SuperPotionEffect',		'Libs/SuperPotionEffect.so'),
       ( 6, 'AtkElectricTalentEffect',		'Libs/AtkElectric_TalentEffect.so'),
       ( 7, 'AtkFireTalentEffect',		'Libs/AtkFire_TalentEffect.so'),
       ( 8, 'AtkTalentEffect',			'Libs/Atk_TalentEffect.so'),
       ( 9, 'BagCapacityTalentEffect',		'Libs/BagCapacity_TalentEffect.so'),
       (10, 'BattleMobTalentEffect',		'Libs/BattleMob_TalentEffect.so'),
       (11, 'CaptureTalentEffect',		'Libs/Capture_TalentEffect.so'),
       (12, 'DefRockTalentEffect',		'Libs/DefRock_TalentEffect.so'),
       (13, 'DefSteelTalentEffect',		'Libs/DefSteel_TalentEffect.so'),
       (14, 'DefTalentEffect',			'Libs/Def_TalentEffect.so'),
       (15, 'HealGrassTalentEffect',		'Libs/HealGrass_TalentEffect.so'),
       (16, 'HealWaterTalentEffect',		'Libs/HealWater_TalentEffect.so'),
       (17, 'HealTalentEffect',			'Libs/Heal_TalentEffect.so'),
       (18, 'HPTalentEffect',			'Libs/HP_TalentEffect.so'),
       (19, 'HealEffect',			'Libs/HealEffect.so'),
       (20, 'HealTargetEffect',			'Libs/HealTargetEffect.so'),
       (21, 'ContreEffect',			'Libs/ContreEffect.so'),
       (22, 'AttiranceEffect',			'Libs/AttiranceEffect.so'),
       (23, 'NormalCartridgeEffect',		'Libs/NormalCartridgeEffect.so'),
       (24, 'SuperCartridgeEffect',		'Libs/SuperCartridgeEffect.so');

/* Inserting Factions */
DELETE FROM `Faction`;

INSERT INTO `Faction`(`id`, `name`, `effectLib`) VALUES
       (1, 'Hesode', 1),
       (2, 'Celestia', 2);

/* Inserting ExperiencesCurves */
DELETE FROM `ExperienceCurve`;

INSERT INTO `ExperienceCurve`(`id`, `name`, `path`) VALUES
       (1, 'FastCurve',		'Libs/FastFunction.so'),
       (2, 'MediumCurve',	'Libs/MediumFunction.so'),
       (3, 'ParabolicCurve',	'Libs/ParabolicFunction.so'),
       (4, 'SlowCurve',		'Libs/SlowFunction.so'),
       (5, 'JobCurve',		'Libs/JobFunction.so'),
       (6, 'PlayerCurve',	'Libs/SlowFunction.so');

/* Inserting TalentModels */
DELETE FROM `TalentModel`;

INSERT INTO `TalentModel`(`id`, `name`, `maxPoints`, `effectLib`) VALUES
       ( 1, 'HP_Talent',			1, 18),
       ( 2, 'Attack_Talent',			3,  8),
       ( 3, 'Defense_Talent',			3, 14),
       ( 4, 'Heal_Talent',			3, 17),
       ( 5, 'Attack_Fire_Talent',		3,  7),
       ( 6, 'Attack_Electric_Talent',		3,  6),
       ( 7, 'Defense_Rock_Talent',		3, 12),
       ( 8, 'Defense_Steel_Talent',		3, 13),
       ( 9, 'Heal_Grass_Talent',		3, 15),
       (10, 'Heal_Water_Talent',		3, 16),
       (11, 'Capture_Talent',			3, 11),
       (12, 'AddBattleMob_Talent',		1, 10),
       (13, 'Limit_Talent',			1,  9),
       (14, 'Capture2_Talent',			3, 11),
       (15, 'AddBattleMob2_Talent',		1, 10);

/* Inserting TalentModels_talents */
DELETE FROM `TalentModel_talents`;

INSERT INTO `TalentModel_talents`(`object_id`, `index`, `value`) VALUES
       ( 1, 0,  2),
       ( 1, 1,  3),
       ( 1, 2,  4),
       ( 2, 0,  5),
       ( 2, 1,  6),
       ( 3, 0,  7),
       ( 3, 1,  8),
       ( 4, 0,  9),
       ( 4, 1, 10),
       (11, 0, 12),
       (12, 0, 13),
       (13, 0, 14),
       (14, 0, 15);

/* Inserting Talents */
DELETE FROM `Talent`;

INSERT INTO `Talent`(`id`, `model`, `currentPoints`) VALUES
       (1,  1, 0),
       (2, 11, 0);

/* Inserting TalentTrees */
DELETE FROM `TalentTree`;

INSERT INTO `TalentTree`(`id`, `name`) VALUES
       (1, 'BaseTree1');

DELETE FROM `TalentTree_talents`;

INSERT INTO `TalentTree_talents`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 11);

/* Inserting DBZones */
DELETE FROM `DBZone`;

INSERT INTO `DBZone`(`id`, `name`, `averageLevel`) VALUES
       (1, 'Plain',	10),
       (2, 'Rock',	20);

/* Inserting Types */
DELETE FROM `Type`;

INSERT INTO `Type`(`id`, `name`) VALUES
       (1, 'Fire'),
       (2, 'Water'),
       (3, 'Grass'),
       (4, 'Electric'),
       (5, 'Rock'),
       (6, 'Steel'),
       (7, 'Normal');

/* Assigning Types to Types */
DELETE FROM `Type_relations`;

INSERT INTO `Type_relations`(`object_id`, `value_oType_id`, `value_coeff`) VALUES
       (1, 1, 0.5),
       (1, 2, 0.5),
       (1, 3,   2),
       (1, 4,   1),
       (1, 5, 0.5),
       (1, 6,   2),
       (2, 1,   2),
       (2, 2, 0.5),
       (2, 3, 0.5),
       (2, 4,   1),
       (2, 5,   2),
       (2, 6,   1),
       (3, 1, 0.5),
       (3, 2,   2),
       (3, 3, 0.5),
       (3, 4,   1),
       (3, 5,   2),
       (3, 6, 0.5),
       (4, 1,   1),
       (4, 2,   2),
       (4, 3, 0.5),
       (4, 4, 0.5),
       (4, 5,   1),
       (4, 6,   1),
       (5, 1,   2),
       (5, 2,   1),
       (5, 3,   1),
       (5, 4,   1),
       (5, 5,   1),
       (5, 6, 0.5),
       (6, 1, 0.5),
       (6, 2, 0.5),
       (6, 3,   1),
       (6, 4, 0.5),
       (6, 5,   2),
       (6, 6, 0.5);

/* Inserting StatKeys */
DELETE FROM `StatKey`;

INSERT INTO `StatKey`(`id`, `name`, `shortLived`) VALUES
       ( 1, 'HP',		0), /* Keep */
       ( 2, 'Attack',		1), /* Keep */
       ( 3, 'Defense',		1), /* Keep */
       ( 4, 'Speed',		1), /* Keep */
       ( 5, 'Heal',		1),

       ( 6, 'Capture',		1),
       ( 7, 'Limit mob',	1),
       ( 8, 'Bag capacity',	1);

/* Inserting AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys`;

INSERT INTO `AuthorizedStatKeys`(`id`, `name`) VALUES
       (1, 'PlayerKeys'),
       (2, 'MobKeys');

/* Assigning StatKeys to AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys_keys`;

INSERT INTO `AuthorizedStatKeys_keys`(`object_id`, `index`, `value`) VALUES
       (1, 0,  6),
       (1, 1,  7),
       (1, 2,  8),
       (2, 0,  1),
       (2, 1,  2),
       (2, 2,  3),
       (2, 3,  4),
       (2, 4,  5);

/* Inserting Guilds */
DELETE FROM `Guild`;

INSERT INTO `Guild`(`id`, `name`) VALUES
       (1, 'Folichon Babbage'),
       (2, 'Les Rageux');

/* Inserting Players */
DELETE FROM Player;

INSERT INTO `Player`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `faction`, `talentTree`, `user`, `guild`, `dbZone`, `x`, `y`, `inventoryPath`, `money`, `limit`, `expCurve`, `currentPts`) VALUES
       (1, 'Thinenus', 1, 0, 1, 10, 1, 1, 1, 1, 1, 10, 30, 'Res/Inventories/Thinenus.json', 10000, 30, 6, 5),
       (2, 'Sezu-Kho', 1, 0, 1, 10, 1, 1, 2, 1, 1, 20, 20, 'Res/Inventories/Sezu-Kho.json', 10000, 30, 6, 0);

/* Assigning CartridgeCip to Players */
DELETE FROM `Player_cartridgeClip`;

INSERT INTO `Player_cartridgeClip`(`object_id`, `key`, `value`) VALUES
       (1, 1, 10),
       (2, 1, 10);

/* Assigning Talents to Players */
DELETE FROM `Player_talents`;

INSERT INTO `Player_talents`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (2, 0, 2);

/* Inserting MobModels */
DELETE FROM `MobModel`;

INSERT INTO `MobModel`(`id`, `name`, `authKeys`, `type`, `expCurve`, `expSeed`, `catchRate`, `dropPath`) VALUES
       (1, 'Charizard',		2, 1, 3, 209,  45, 'Res/Drops/Charizard.json'),
       (2, 'Blastoise',		2, 2, 3, 210,  45, 'Res/Drops/Blastoise.json'),
       (3, 'Venusaur',		2, 3, 3, 208,  45, 'Res/Drops/Venusaur.json'),
       (4, 'Pikachu',		2, 4, 2,  82, 190, 'Res/Drops/Pikachu.json'),
       (5, 'Sudowoodo',		2, 5, 3, 135,  65, 'Res/Drops/Sudowoodo.json'),
       (6, 'Klink',		2, 6, 3,  60, 130, 'Res/Drops/Klink.json');

/* Inserting Ressources */
DELETE FROM `Ressource`;

INSERT INTO `Ressource`(`id`, `name`, `gather`, `level`, `exp`) VALUES
       ( 1, 'Orchidee',			1, 10, 100),
       ( 2, 'Peau de bouftou',		1,  1,  10),
       ( 3, 'Tree',			0,  0,   0),
       ( 4, 'Venuzaur Leaf',		1,  0,   0),
       ( 5, 'Charizard Tooth',		1,  0,   0),
       ( 6, 'Blastoise Scale',		1,  0,   0),
       ( 7, 'Bone',			0,  0,   0),
       ( 8, 'Bush',			0,  0,   0),
       ( 9, 'House',			0,  0,   0),
       (10, 'Cuivre',			1,  0, 100);

/* Assigning Ressources to MobModels */
DELETE FROM `MobModel_carcass`;

INSERT INTO `MobModel_carcass`(`object_id`, `ressource`, `nb`) VALUES
       (1, 5,  4),
       (2, 6, 10),
       (3, 4,  5);

/* Inserting Spells */
DELETE FROM `Spell`;

INSERT INTO `Spell`(`id`, `name`, `type`, `power`, `useLimit`, `effectLib`) VALUES
       (1,  'Lance-Flamme',	1,  90, 0,  3),
       (2,  'Flammeche',	1,  40, 0,  3),
       (3,  'Crocs Feu',	1,  65, 0,  3),
       (4,  'Boutefeu',		1, 120, 0,  3),
       (5,  'Vibraqua',		2,  60, 0,  3),
       (6,  'Hydroqueue',	2,  90, 0,  3),
       (7,  'Hydrocanon',	2, 110, 0,  3),
       (8,  'Surf',		2,  90, 0,  3),
       (9,  'Tranch''Herbe',	3,  55, 0,  3),
       (10, 'Fouet Lianes',	3,  35, 0,  3),
       (11, 'Danse-Fleur',	3, 120, 0,  3),
       (12, 'Lance-Soleil',	3, 120, 0,  3),
       (13, 'Crocs Eclair',	4,  65, 0,  3),
       (14, 'Fatal-Foudre',	4, 110, 0,  3),
       (15, 'Onde de Choc',	4,  60, 0,  3),
       (16, 'Tonnerre',		4,  90, 0,  3),
       (17, 'Eboulement',	5,  75, 0,  3),
       (18, 'Tomberoche',	5,  65, 0,  3),
       (19, 'Jet-Pierres',	5,  50, 0,  3),
       (20, 'Lame de Roc',	5, 100, 0,  3),
       (21, 'Tete de Fer',	6,  80, 0,  3),
       (22, 'Gyroballe',	6,  25, 0,  3),
       (23, 'Poing Meteor',	6,  90, 0,  3),
       (24, 'Tacle lourd',	6, 100, 0,  3),
       (25, 'Mega-Sangsue',	3,  40, 0, 19),
       (26, 'Absorption',	2,  60, 0, 19),
       (27, 'Soin',		3,   0, 0, 20),
       (28, 'Contre',		7,   0, 0, 21),
       (29, 'Attirance',	7,   0, 0, 22);

/* Assigning Spells to MobModels */
DELETE FROM `MobModel_spells`;

INSERT INTO `MobModel_spells`(`object_id`, `index`, `value`) VALUES
       /* Charizard */
       (1, 0,  1),
       (1, 1,  2),
       (1, 2,  3),
       (1, 3,  4),
       (1, 4, 28),
       (1, 5, 29),
       /* Blastoise */
       (2, 0,  5),
       (2, 1,  6),
       (2, 2,  7),
       (2, 3,  8),
       (2, 4, 26),
       /* Venusaur */
       (3, 0,  9),
       (3, 1, 10),
       (3, 2, 11),
       (3, 3, 12),
       (3, 4, 27),
       (3, 5, 25),
       /* Pikachu */
       (4, 0, 13),
       (4, 1, 14),
       (4, 2, 15),
       (4, 3, 16),
       /* Sudowoodo */
       (5, 0, 17),
       (5, 1, 18),
       (5, 2, 19),
       (5, 3, 20),
       (5, 4, 29),
       /* Klink */
       (6, 0, 21),
       (6, 1, 22),
       (6, 2, 23),
       (6, 3, 24),
       (6, 4, 29);

/* Assigning Stats to MobModels */
DELETE FROM `MobModel_stats`;

INSERT INTO `MobModel_stats`(`object_id`, `key`, `value`) VALUES
       /* Charizard OK */
       ( 1,  1,  78),
       ( 1,  2,  84),
       ( 1,  3,  78),
       ( 1,  4, 100),
       ( 1,  5,  10),
       /* Blastoise OK */
       ( 2,  1,  79),
       ( 2,  2,  83),
       ( 2,  3, 100),
       ( 2,  4,  78),
       ( 2,  5,  80),
       /* Venusaur OK */
       ( 3,  1,  80),
       ( 3,  2,  82),
       ( 3,  3,  83),
       ( 3,  4,  80),
       ( 3,  5, 100),
       /* Pikachu OK */
       ( 4,  1,  35), /*  PV   */
       ( 4,  2,  55), /*  Atk  */
       ( 4,  3,  40), /*  Def  */
       ( 4,  4,  90), /*  Vit  */
       ( 4,  5,  10), /*  As  */
       /* Sudowoodo OK */
       ( 5,  1,  70),
       ( 5,  2, 100),
       ( 5,  3, 115),
       ( 5,  4,  30),
       ( 5,  5,  10),
       /* Klink OK */
       ( 6,  1,  40),
       ( 6,  2,  55),
       ( 6,  3,  70),
       ( 6,  4,  30),
       ( 6,  5,  10);

/* Inserting Mobs */
DELETE FROM `Mob`;

INSERT INTO `Mob`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `model`) VALUES
       (1, 'Charizard',		2, 36435, 35, 40007, 1),
       (2, 'Blastoise',		2,  2035, 15,  2535, 2),
       (3, 'Venuzaur',		2,  3120, 17,  3798, 3),
       (4, 'Charizard',		2,  3120, 17,  3798, 1),
       (5, 'Blastoise',		2, 36435, 35, 40007, 2),
       (6, 'Venuzaur',		2,  2035, 15,  2535, 3),
       (7, 'Pikachu',		2,  3375, 15,  4096, 4),
       (8, 'Pikachu',		2,  3375, 15,  4096, 4);

/* Inserting JobModels */
DELETE FROM `JobModel`;

INSERT INTO `JobModel`(`id`, `name`, `path`, `expCurve`) VALUES
        (1, 'Developpeur',        'Res/JobCraft/developpeur.json', 5),
        (2, 'Armurier',	          'Res/JobCraft/armurier.json', 5),
        (3, 'Ingenieur',          'Res/JobCraft/ingenieur.json', 5),
        (4, 'Maitre des Potions', 'Res/JobCraft/potions.json', 5),
	(5, 'Herboriste',	  'Res/JobCraft/herboriste.json', 5),
	(6, 'Mineur',		  'Res/JobCraft/mineur.json', 5),
	(7, 'Trappeur',		  'Res/JobCraft/trappeur.json', 5);

/* Assigning gathers to JobModels */
DELETE FROM `JobModel_gathers`;

INSERT INTO `JobModel_gathers`(`object_id`, `index`, `value_level`, `value_exp`, `value_ressource`) VALUES
       (5, 0, 1, 10, 1),
       (7, 0, 1, 10, 2),
       (7, 1, 1, 10, 4),
       (7, 2, 1, 10, 5),
       (7, 3, 1, 10, 6),
       (7, 4, 1, 10, 7),
       (6, 0, 1, 10, 10);

/* Inserting Job */
DELETE FROM `Job`;

INSERT INTO `Job`(`id`, `currentExp`, `level`, `exp`, `jobModel`) VALUES
       (  1, 0, 0, 100, 1),
       (  2, 0, 0, 100, 2),
       (  3, 0, 0, 100, 3),
       (  4, 0, 0, 100, 4),
       (  5, 0, 0, 100, 5),
       (  6, 0, 0, 100, 6),
       (  7, 0, 0, 100, 7),
       (  8, 0, 0, 100, 1),
       (  9, 0, 0, 100, 2),
       ( 10, 0, 0, 100, 3),
       ( 11, 0, 0, 100, 4),
       ( 12, 0, 0, 100, 5),
       ( 13, 0, 0, 100, 6),
       ( 14, 0, 0, 100, 7);

/*  Assigning Jobs to Players */
DELETE FROM `Player_jobs`;

INSERT INTO `Player_jobs`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 4),
       (1, 4, 5),
       (1, 5, 6),
       (1, 6, 7),
       (2, 0, 8),
       (2, 1, 9),
       (2, 2, 10),
       (2, 3, 11),
       (2, 4, 12),
       (2, 5, 13),
       (2, 6, 14);

/* Assigning Mobs to Players */
DELETE FROM `Player_mobs`;

/* Assigning Mobs to Players */
DELETE FROM `Player_battleMobs`;

INSERT INTO `Player_battleMobs`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 7),
       (2, 0, 4),
       (2, 1, 5),
       (2, 2, 6),
       (2, 3, 8);

/* Assigning Mobmodels to DBZone */
DELETE FROM `DBZone_mobModels`;

INSERT INTO `DBZone_mobModels`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 4),
       (2, 0, 4),
       (2, 1, 5),
       (2, 2, 6);

/* Inserting Stuff */
DELETE FROM `Stuff`;

INSERT INTO `Stuff`(`id`, `name`, `stuffType`) VALUES
       ( 1, 'Bouftou Helmet', 'HELMET'),
       ( 2, 'Bouftou Cloak', 'CLOAK'),
       ( 3, 'Bouftou Boots', 'BOOTS'),
       ( 4, 'Bouftou Necklace', 'NECKLACE'),
       ( 5, 'Bouftou Shoulders', 'SHOULDERS'),
       ( 6, 'Bouftou Breastplate', 'BREASTPLATE'),
       ( 7, 'Bouftou Ring', 'RING'),
       ( 8, 'Bouftou Belt', 'BELT'),
       ( 9, 'Bouftou Hammer', 'WEAPON'),
       (10, 'Piou Helmet', 'HELMET'),
       (11, 'Charizard Skull', 'HELMET'),
       (12, 'Blastoise Canon', 'SHOULDERS'),
       (13, 'Venusaur Leafs', 'CLOAK'),
       (14, 'Black Helmet', 'HELMET'),
       (15, 'Diamond Breastplate', 'BREASTPLATE'),
       (16, 'Egyptian Necklace', 'NECKLACE'),
       (17, 'Fantomas Boots', 'BOOTS'),
       (18, 'Frodos Ring', 'RING'),
       (19, 'Gold Helmet', 'HELMET'),
       (20, 'Warrior Helmet', 'HELMET'),
       (21, 'Leather Boots', 'BOOTS'),
       (22, 'Pendala Necklace', 'NECKLACE'),
       (23, 'Power Ring', 'RING'),
       (24, 'Poor Ring', 'RING'),
       (25, 'Slayer Cloak', 'CLOAK'),
       (26, 'Vampire Cloak', 'CLOAK');

/* Inserting Stuff */
DELETE FROM `Stuff_stats`;

INSERT INTO `Stuff_stats`(`object_id`, `key`, `value`) VALUES
       ( 1, 1,  20),
       ( 1, 2,   5),
       ( 2, 1,  20),
       ( 2, 3,   5),
       ( 3, 3,   5),
       ( 3, 4,  15),
       ( 4, 1,  20),
       ( 4, 5,   4),
       ( 5, 5,   4),
       ( 5, 2,   5),
       ( 6, 1,  20),
       ( 6, 3,   5),
       ( 7, 1,  20),
       ( 7, 5,   4),
       ( 8, 1,  20),
       ( 8, 2,   5),
       ( 9, 1,  20),
       ( 9, 2,   5),
       (10, 4,  15),
       (10, 2,   5),
       (11, 2,  10),
       (12, 2,  10),
       (13, 2,  10),
       (14, 4,  10),
       (15, 5,  10),
       (16, 4,  10),
       (17, 1,  10),
       (18, 4,  10),
       (19, 2,  10),
       (20, 4,  10),
       (21, 3,  10),
       (22, 1,  10),
       (23, 2,  10);

/* Assigning Stuff to Players */
DELETE FROM `Player_equipment`;

INSERT INTO `Player_equipment`(`object_id`, `key`, `value`) VALUES
       (1, 'HELMET', 1),
       (1, 'BREASTPLATE', 6),
       (1, 'SHOULDERS', 5),
       (1, 'CLOAK', 26),
       (2, 'WEAPON', 9),
       (2, 'BELT', 8),
       (2, 'RING', 7),
       (2, 'BOOTS', 3);

/* Assigning Stats to Players */
DELETE FROM `Player_stats`;

INSERT INTO `Player_stats`(`object_id`, `key`, `value`) VALUES
       ( 1,  6,  10),
       ( 1,  7,  12),
       ( 1,  8,  40),
       ( 2,  6,  20),
       ( 2,  7,  22),
       ( 2,  8,  50);

/* Inserting Heals */
DELETE FROM `Heal`;

INSERT INTO `Heal`(`id`, `name`, `pnjType`, `zone`, `x`, `y`) VALUES
       (1, 'Healer0', 'HEAL', 'Plain', 10, 70),
       (2, 'Healer1', 'HEAL', 'Rock', 30, 30),
       (3, 'Healer2', 'HEAL', 'Plain', 40, 40);

/* Inserting Consumable */
DELETE FROM `Consumable`;

INSERT INTO `Consumable`(`id`, `name`, `forMob`, `effectlib`) VALUES
       (1, 'Potion',			1,	 4),
       (2, 'Super Potion',		1,	 5),
       (3, 'Normal Cartridge x10',	0,	23),
       (4, 'Super Cartridge x10',	0,	24);

/* Adding some fancy views because it's quite swag */
-- DROP VIEW IF EXISTS `StatView`;
-- CREATE VIEW StatView AS SELECT Stat.id, StatKey.name, Stat.value FROM Stat, StatKey WHERE Stat.key = StatKey.id;

-- DROP VIEW IF EXISTS `MobModelView`;
-- CREATE VIEW MobModelView AS 
--        SELECT MobModel.id, MobModel.name AS model, Type.name AS type, StatView.name AS stat, StatView.value
--        	      FROM StatView, Type, MobModel_stats, MobModel
--        	      WHERE MobModel_stats.value = StatView.id
--        	      	    AND MobModel_stats.object_id = MobModel.id
-- 	     	    AND MobModel.type = Type.id;

-- DROP VIEW IF EXISTS `MobView`;
-- CREATE VIEW `MobView` AS
--        SELECT Mob.id, Mob.name, Mob.level, MobModelView.model, MobModelView.type, MobModelView.stat, MobModelView.value AS modelValue, StatView.value AS mobValue
--        	      FROM Mob, MobModelView, Mob_stats, StatView
--        	      WHERE Mob.model = MobModelView.id
-- 	      	    AND Mob_stats.object_id = Mob.id
-- 	      	    AND StatView.id = Mob_stats.value
-- 		    AND StatView.name = MobModelView.stat;

-- DROP VIEW IF EXISTS `PlayerView`;
-- CREATE VIEW `PlayerView` AS
--        SELECT Player.id, Player.name, User.pseudo AS user, Faction.name AS faction, Player.level, Player.currentExp, DBZone.name AS zone, Player.x, Player.y,
--        	      AuthorizedStatKeys.name AS statKeys, TalentTree.name AS talentTree, StatView.name AS stat, StatView.value
--        	      FROM Player, Faction, User, DBZone, AuthorizedStatKeys, TalentTree, StatView, Player_stats
--        	      WHERE Player.faction = Faction.id
--        	      	    AND Player.user = User.id
-- 	     	    AND Player.dbZone = DBZone.id
-- 		    AND Player.authKeys = AuthorizedStatKeys.id
-- 		    AND Player.talentTree = TalentTree.id
-- 		    AND Player_stats.object_id = Player.id
-- 		    AND Player_stats.value = StatView.id
-- 	      ORDER BY Player.id;

-- DROP VIEW IF EXISTS `TypeView`;
-- CREATE VIEW `TypeView` AS
--        SELECT Type.id, Type.name, OType.name AS other, Type_relations.value_coeff AS coeff
--        	      FROM Type, Type AS OType, Type_relations
-- 	      WHERE Type_relations.object_id = Type.id
-- 	      	    AND Type_relations.value_oType_id = OType.id
-- 	      ORDER BY Type.id, OType.id;

COMMIT;

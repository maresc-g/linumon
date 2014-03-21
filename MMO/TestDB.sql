BEGIN;

/* Inserting Users */
DELETE FROM `User`;

INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES
       (1, 'Laurent', 'yolo'),
       (2, 'Cyril', 'swag');

/* Inserting EffectLibs */
DELETE FROM `EffectLib`;

INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES
       (1, 'HesodeEffect', 'Libs/HesodeEffect.so'),
       (2, 'CelestiaEffect', 'Libs/CelestiaEffect.so'),
       (3, 'NormalEffect', 'Libs/NormalEffect.so'),
       (4, 'PotionEffect', 'Libs/PotionEffect.so'),
       (5, 'SuperPotionEffect', 'Libs/SuperPotionEffect.so');

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
       ( 1, 'HP_Talent',			1, 1),
       ( 2, 'Attack_Talent',			3, 1),
       ( 3, 'Defense_Talent',			3, 1),
       ( 4, 'Heal_Talent',			3, 1),
       ( 5, 'Attack_Fire_Talent',		3, 1),
       ( 6, 'Attack_Electric_Talent',		3, 1),
       ( 7, 'Defense_Rock_Talent',		3, 1),
       ( 8, 'Defense_Steel_Talent',		3, 1),
       ( 9, 'Heal_Grass_Talent',		3, 1),
       (10, 'Heal_Water_Talent',		3, 1),
       (11, 'Capture_Talent',			3, 1),
       (12, 'AddBattleMob_Talent',		1, 1),
       (13, 'Limit_Talent',			1, 1),
       (14, 'Capture2_Talent',			3, 1),
       (15, 'AddBattleMob2_Talent',		1, 1);

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
       (1, 1, 0),
       (2, 2, 0);

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
       (6, 'Steel');

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
       ( 1, 'HP',		0),
       ( 2, 'Attack',		1),
       ( 3, 'Defense',		1),
       ( 4, 'Speed',		1),
       ( 5, 'Precision',	1),
       ( 6, 'Dodge',		1),
       ( 7, 'Parade',		1),
       ( 8, 'Critic',		1),

       ( 9, 'Capture',		1),
       (10, 'Limit mob',	1),
       (11, 'Bag capacity',	1);

/* Inserting AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys`;

INSERT INTO `AuthorizedStatKeys`(`id`, `name`) VALUES
       (1, 'PlayerKeys'),
       (2, 'MobKeys');

/* Assigning StatKeys to AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys_keys`;

INSERT INTO `AuthorizedStatKeys_keys`(`object_id`, `index`, `value`) VALUES
       (1, 0,  2),
       (1, 1,  3),
       (1, 2,  9),
       (1, 3, 10),
       (1, 4, 11),
       (2, 0,  1),
       (2, 1,  2),
       (2, 2,  3),
       (2, 3,  4),
       (2, 4,  5),
       (2, 5,  6),
       (2, 6,  7),
       (2, 7,  8);

/* Inserting Guilds */
DELETE FROM `Guild`;

INSERT INTO `Guild`(`id`, `name`) VALUES
       (1, 'Folichon Babbage'),
       (2, 'Les Rageux');

/* Inserting Players */
DELETE FROM Player;

INSERT INTO `Player`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `faction`, `talentTree`, `user`, `guild`, `dbZone`, `x`, `y`, `digitaliserEfficiency`, `inventoryPath`, `money`, `limit`, `expCurve`, `currentPts`) VALUES
       (1, 'Thinenus', 1, 0, 1, 10, 1, 1, 1, 1, 1, 10, 30, 1, 'Res/Inventories/Thinenus.json', 10000, 30, 6, 5),
       (2, 'Sezu-Kho', 1, 0, 1, 10, 1, 1, 2, 1, 1, 20, 20, 1, 'Res/Inventories/Sezu-Kho.json', 10000, 30, 6, 0);

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
       (1, 'Orchidee',			1, 10, 100),
       (2, 'Peau de bouftou',		1,  1,  10),
       (3, 'Tree',			0,  0,   0),
       (4, 'Feuille de Venuzaur',	1,  0,   0),
       (5, 'Dent de Charizard',		1,  0,   0),
       (6, 'Ecaille de Blastoise',	1,  0,   0),
       (7, 'Os',			0,  0,   0),
       (8, 'Bush',			0,  0,   0),
       (9, 'House',			0,  0,   0);

/* Assigning Ressources to MobModels */
DELETE FROM `MobModel_carcass`;

INSERT INTO `MobModel_carcass`(`object_id`, `ressource`, `nb`) VALUES
       (1, 5,  4),
       (2, 6, 10),
       (3, 4,  5);

/* Inserting Spells */
DELETE FROM `Spell`;

INSERT INTO `Spell`(`id`, `name`, `type`, `power`, `useLimit`, `effectLib`) VALUES
       (1,  'Lance-Flamme',	1,  90, 0, 3),
       (2,  'Flammeche',	1,  40, 0, 3),
       (3,  'Crocs Feu',	1,  65, 0, 3),
       (4,  'Boutefeu',		1, 120, 0, 3),
       (5,  'Vibraqua',		2,  60, 0, 3),
       (6,  'Hydroqueue',	2,  90, 0, 3),
       (7,  'Hydrocanon',	2, 110, 0, 3),
       (8,  'Surf',		2,  90, 0, 3),
       (9,  'Tranch''Herbe',	3,  55, 0, 3),
       (10, 'Fouet Lianes',	3,  35, 0, 3),
       (11, 'Danse-Fleur',	3, 120, 0, 3),
       (12, 'Lance-Soleil',	3, 120, 0, 3),
       (13, 'Crocs Eclair',	4,  65, 0, 3),
       (14, 'Fatal-Foudre',	4, 110, 0, 3),
       (15, 'Onde de Choc',	4,  60, 0, 3),
       (16, 'Tonnerre',		4,  90, 0, 3),
       (17, 'Eboulement',	5,  75, 0, 3),
       (18, 'Tomberoche',	5,  65, 0, 3),
       (19, 'Jet-Pierres',	5,  50, 0, 3),
       (20, 'Lame de Roc',	5, 100, 0, 3),
       (21, 'Tete de Fer',	6,  80, 0, 3),
       (22, 'Gyroballe',	6,  25, 0, 3),
       (23, 'Poing, Meteor',	6,  90, 0, 3),
       (24, 'Tacle lourd',	6, 100, 0, 3);

/* Assigning Spells to MobModels */
DELETE FROM `MobModel_spells`;

INSERT INTO `MobModel_spells`(`object_id`, `index`, `value`) VALUES
       /* Charizard */
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 4),
       /* Blastoise */
       (2, 0, 5),
       (2, 1, 6),
       (2, 2, 7),
       (2, 3, 8),
       /* Venusaur */
       (3, 0, 9),
       (3, 1, 10),
       (3, 2, 11),
       (3, 3, 12),
       /* Pikachu */
       (4, 0, 13),
       (4, 1, 14),
       (4, 2, 15),
       (4, 3, 16);

/* Assigning Stats to MobModels */
DELETE FROM `MobModel_stats`;

INSERT INTO `MobModel_stats`(`object_id`, `key`, `value`) VALUES
       /* Charizard OK */
       ( 1,  1,  78),
       ( 1,  2,  84),
       ( 1,  3,  78),
       ( 1,  4, 100),
       ( 1,  5, 109),
       ( 1,  6, 100),
       ( 1,  7,  85),
       ( 1,  8, 109),
       /* Blastoise OK */
       ( 2,  1,  79),
       ( 2,  2,  83),
       ( 2,  3, 100),
       ( 2,  4,  78),
       ( 2,  5,  85),
       ( 2,  6,  78),
       ( 2,  7, 105),
       ( 2,  8,  85),
       /* Venusaur OK */
       ( 3,  1,  80),
       ( 3,  2,  82),
       ( 3,  3,  83),
       ( 3,  4,  80),
       ( 3,  5, 100),
       ( 3,  6,  80),
       ( 3,  7, 100),
       ( 3,  8, 100),
       /* Pikachu OK */
       ( 4,  1,  35), /*  PV   */
       ( 4,  2,  55), /*  Atk  */
       ( 4,  3,  40), /*  Def  */
       ( 4,  4,  90), /*  Vit  */
       ( 4,  5,  50), /*  As  */
       ( 4,  6,  90), /*  Vit  */
       ( 4,  7,  50), /*  Ds   */
       ( 4,  8,  50), /*  As   */
       /* Sudowoodo OK */
       ( 5,  1,  70),
       ( 5,  2, 100),
       ( 5,  3, 115),
       ( 5,  4,  30),
       ( 5,  5,  30),
       ( 5,  6,  30),
       ( 5,  7,  65),
       ( 5,  8,  30),
       /* Klink OK */
       ( 6,  1,  40),
       ( 6,  2,  55),
       ( 6,  3,  70),
       ( 6,  4,  30),
       ( 6,  5,  45),
       ( 6,  6,  30),
       ( 6,  7,  60),
       ( 6,  8,  45);

/* Inserting Mobs */
DELETE FROM `Mob`;

INSERT INTO `Mob`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `model`) VALUES
       (1, 'TinyLezard',	2, 36435, 35, 40007, 1),
       (2, 'BigTurtle',		2,  2035, 15,  2535, 2),
       (3, 'VastFlowerPot',	2,  3120, 17,  3798, 3),
       (4, 'MegaFist',		2,  3120, 17,  3798, 1),
       (5, 'SuperWet',		2, 36435, 35, 40007, 2),
       (6, 'UltraBushy',	2,  2035, 15,  2535, 3),
       (7, 'Pikabillaud',	2,  3375, 15,  4096, 4),
       (8, 'Pikatheorie',	2,  3375, 15,  4096, 4);

/* Assigning Stats to Mobs */
DELETE FROM `Mob_stats`;

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
       (7, 0, 1, 10, 2);

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
       ( 1, 'Coiffe Bouftou', 'HELMET'),
       ( 2, 'Cape Bouftou', 'CLOAK'),
       ( 3, 'Bottes Bouftou', 'BOOTS'),
       ( 4, 'Amulette Bouftou', 'NECKLACE'),
       ( 5, 'Epaulettes Bouftou', 'SHOULDERS'),
       ( 6, 'Plastron Bouftou', 'BREASTPLATE'),
       ( 7, 'Anneau Bouftou', 'RING'),
       ( 8, 'Ceinture Bouftou', 'BELT'),
       ( 9, 'Marteau Bouftou', 'WEAPON'),
       (10, 'Casque Piou', 'HELMET'),
       (11, 'Crane de Charizard', 'HELMET'),
       (12, 'Canons de Blastoise', 'SHOULDERS'),
       (13, 'Feuillage de Venusaur', 'CLOAK');

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
       ( 4, 6,   4),
       ( 5, 6,   4),
       ( 5, 2,   5),
       ( 6, 1,  20),
       ( 6, 3,   5),
       ( 7, 1,  20),
       ( 7, 6,   4),
       ( 8, 1,  20),
       ( 8, 2,   5),
       ( 9, 1,  20),
       ( 9, 2,   5),
       (10, 4,  15),
       (10, 2,   5),
       (11, 2,  10),
       (12, 2,  10),
       (13, 2,  10);

/* Assigning Stuff to Players */
DELETE FROM `Player_equipment`;

INSERT INTO `Player_equipment`(`object_id`, `key`, `value`) VALUES
       (1, 'HELMET', 1),
       (1, 'BREASTPLATE', 6),
       (1, 'SHOULDERS', 5),
       (1, 'CLOAK', 2),
       (2, 'WEAPON', 9),
       (2, 'BELT', 8),
       (2, 'RING', 7),
       (2, 'BOOTS', 3);

/* Assigning Stats to Players */
DELETE FROM `Player_stats`;

INSERT INTO `Player_stats`(`object_id`, `key`, `value`) VALUES
       ( 1,  9,  10),
       ( 1, 10,  12),
       ( 1, 11,  40),
       ( 2,  9,  20),
       ( 2, 10,  22),
       ( 2, 11,  50);

/* Inserting Heals */
DELETE FROM `Heal`;

INSERT INTO `Heal`(`id`, `name`, `pnjType`, `zone`, `x`, `y`) VALUES
       (1, 'Healer0', 'HEAL', 'Plain', 10, 70),
       (2, 'Healer1', 'HEAL', 'Plain', 30, 30),
       (3, 'Healer2', 'HEAL', 'Plain', 40, 40);

/* Inserting Consumable */
DELETE FROM `Consumable`;

INSERT INTO `Consumable`(`id`, `name`, `effectlib`) VALUES
       (1, 'Potion', 4),
       (2, 'Super Potion', 5);

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

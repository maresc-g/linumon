BEGIN;

/* Inserting Users */
DELETE FROM `User`;

INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES
       (1, 'Laurent', 'yolo'),
       (2, 'Cyril', 'swag');

/* Inserting EffectLibs */
DELETE FROM `EffectLib`;

INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES
       (1, 'Rugissement', 'Libs/Rugissement.so'),
       (2, 'Mimi-Queue', 'Libs/Mimi-Queue.so'),
       (3, 'HesodeEffect', 'Libs/HesodeEffect.so'),
       (4, 'CelestiaEffect', 'Libs/CelestiaEffect.so'),
       (5, 'NormalEffect', 'Libs/NormalEffect.so'),
       (6, 'PotionEffect', 'Libs/PotionEffect.so'),
       (7, 'SuperPotionEffect', 'Libs/SuperPotionEffect.so');

/* Inserting Factions */
DELETE FROM `Faction`;

INSERT INTO `Faction`(`id`, `name`, `effectLib`) VALUES
       (1, 'Hesode', 3),
       (2, 'Celestia', 4);

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
       (1, 'MinAtkTalentModel', 10, 1),
       (2, 'MinDefTalentModel', 10, 2);

/* Inserting TalentModels_talents */
DELETE FROM `TalentModel_talents`;

INSERT INTO `TalentModel_talents`(`object_id`, `index`, `value`) VALUES
       (1, 0, 2);

/* Inserting Talents */
DELETE FROM `Talent`;

INSERT INTO `Talent`(`id`, `model`, `currentPoints`) VALUES
       (1, 1, 0),
       (2, 2, 0);

/* Inserting TalentTrees */
DELETE FROM `TalentTree`;

INSERT INTO `TalentTree`(`id`, `name`, `talent`) VALUES
       (1, 'BaseTree1', 1),
       (2, 'BaseTree2', 2);

/* Inserting DBZones */
DELETE FROM `DBZone`;

INSERT INTO `DBZone`(`id`, `name`, `averageLevel`) VALUES
       (1, 'Plain', 20),
       (2, 'Rock', 40);

/* Inserting Types */
DELETE FROM `Type`;

INSERT INTO `Type`(`id`, `name`) VALUES
       (1, 'Fire'),
       (2, 'Water'),
       (3, 'Grass'),
       (4, 'Electric');

/* Assigning Types to Types */
DELETE FROM `Type_relations`;

INSERT INTO `Type_relations`(`object_id`, `index`, `value_oType_id`, `value_coeff`) VALUES
       (1, 0, 1, 0.5),
       (1, 1, 2, 0.5),
       (1, 2, 3, 2),
       (1, 3, 4, 1),
       (2, 0, 1, 2),
       (2, 1, 2, 0.5),
       (2, 2, 3, 0.5),
       (2, 3, 4, 1),
       (3, 0, 1, 0.5),
       (3, 1, 2, 2),
       (3, 2, 3, 0.5),
       (3, 3, 4, 1),
       (4, 0, 1, 1),
       (4, 1, 2, 2),
       (4, 2, 3, 0.5),
       (4, 3, 4, 0.5);

/* Inserting StatKeys */
DELETE FROM `StatKey`;

INSERT INTO `StatKey`(`id`, `name`, `shortLived`) VALUES
       (1, 'HP', 0),
       (2, 'Attack', 1),
       (3, 'Defense', 1),
       (4, 'Speed', 1),
       (5, 'Precision', 1),
       (6, 'Dodge', 1),
       (7, 'Parade', 1),
       (8, 'Critic', 1),
       (9, 'Capture', 1),
       (10, 'Limit mob', 1),
       (11, 'Bag capacity', 1);

/* Inserting AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys`;

INSERT INTO `AuthorizedStatKeys`(`id`, `name`) VALUES
       (1, 'PlayerKeys'),
       (2, 'MobKeys');

/* Assigning StatKeys to AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys_keys`;

INSERT INTO `AuthorizedStatKeys_keys`(`object_id`, `index`, `value`) VALUES
       (1, 0, 2),
       (1, 1, 3),
       (1, 2, 9),
       (1, 3, 10),
       (1, 4, 11),
       (2, 0, 1),
       (2, 1, 2),
       (2, 2, 3),
       (2, 3, 4),
       (2, 4, 5),
       (2, 5, 6),
       (2, 6, 7),
       (2, 7, 8);

/* Inserting Guilds */
DELETE FROM `Guild`;

INSERT INTO `Guild`(`id`, `name`) VALUES
       (1, 'Folichon Babbage'),
       (2, 'Les Rageux');

/* Inserting Players */
DELETE FROM Player;

INSERT INTO `Player`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `faction`, `talentTree`, `user`, `guild`, `dbZone`, `x`, `y`, `inventoryPath`, `money`, `limit`, `expCurve`) VALUES
       (1, 'Thinenus', 1, 0, 1, 10, 1, 1, 1, 1, 1, 10, 30, 'Res/Inventories/Thinenus.json', 10000, 30, 6),
       (2, 'Sezu-Kho', 1, 0, 1, 10, 1, 1, 2, 1, 1, 20, 20, 'Res/Inventories/Sezu-Kho.json', 10000, 30, 6);

/* Assigning Talents to Players */
DELETE FROM `Player_talents`;

INSERT INTO `Player_talents`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (2, 0, 2);

/* Inserting MobModels */
DELETE FROM `MobModel`;

INSERT INTO `MobModel`(`id`, `name`, `authKeys`, `type`, `expCurve`) VALUES
       (1, 'Charizard', 2, 1, 3),
       (2, 'Blastoise', 2, 2, 3),
       (3, 'Venusaur',  2, 3, 3),
       (4, 'Pikachu',   2, 4, 2);

/* Assignin MobModels to DBZones */
DELETE FROM `DBZone_mobModels`;

INSERT INTO `DBZone_mobModels`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 4),
       (2, 0, 1),
       (2, 1, 2),
       (2, 2, 3),
       (2, 3, 4);

/* Inserting Spells */
DELETE FROM `Spell`;

INSERT INTO `Spell`(`id`, `name`, `type`, `power`, `useLimit`, `effectLib`) VALUES
       (1,  'Lance-Flamme',  1,  90, 0, 5),
       (2,  'Flammèche',     1,  40, 0, 5),
       (3,  'Crocs Feu',     1,  65, 0, 5),
       (4,  'Boutefeu',      1, 120, 0, 5),
       (5,  'Vibraqua',      2,  60, 0, 5),
       (6,  'Hydroqueue',    2,  90, 0, 5),
       (7,  'Hydrocanon',    2, 110, 0, 5),
       (8,  'Surf',          2,  90, 0, 5),
       (9,  'Tranch''Herbe', 3,  55, 0, 5),
       (10, 'Fouet Lianes',  3,  35, 0, 5),
       (11, 'Danse-Fleur',   3, 120, 0, 5),
       (12, 'Lance-Soleil',  3, 120, 0, 5),
       (13, 'Crocs Eclair',  4,  65, 0, 5),
       (14, 'Fatal-Foudre',  4, 110, 0, 5),
       (15, 'Onde de Choc',  4,  60, 0, 5),
       (16, 'Tonnerre',      4,  90, 0, 5);

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

/* Inserting Stats */
DELETE FROM `Stat`;

INSERT INTO `Stat`(`id`, `key`, `value`) VALUES
       /* Charizard */
       (  1,  1, 78),
       (  2,  2, 84),
       (  3,  3, 78),
       (  4,  4, 100),
       (  5,  5, 109),
       (  6,  6, 100),
       (  7,  7, 85),
       (  8,  8, 109),
       /* Blastoise  */
       (  9,  1,  79),
       ( 10,  2,  83),
       ( 11,  3, 100),
       ( 12,  4,  78),
       ( 13,  5,  85),
       ( 14,  6,  78),
       ( 15,  7, 105),
       ( 16,  8,  85),
       /* Venusaur */
       ( 17,  1,  80),
       ( 18,  2,  82),
       ( 19,  3,  83),
       ( 20,  4,  80),
       ( 21,  5, 100),
       ( 22,  6,  80),
       ( 23,  7, 100),
       ( 24,  8, 100),
       /* Pikachu */
       ( 25,  1,  35),
       ( 26,  2,  55),
       ( 27,  3,  40),
       ( 28,  4,  90),
       ( 29,  5,  50),
       ( 30,  6,  90),
       ( 31,  7,  50),
       ( 32,  8,  50),
       /* Players */
       ( 33,  9,  10),
       ( 34, 10,  12),
       ( 35, 11,  40),
       ( 36,  9,  20),
       ( 37, 10,  22),
       ( 38, 11,  50),

       /* Stuffs */
       ( 39,  1,  20),
       ( 40,  2,   5),
       ( 41,  3,   5),
       ( 42,  4,  15),
       ( 43,  5,   8),
       ( 44,  6,   4),
       ( 45,  7,   1),
       ( 46,  8,   3);

/* Assigning Stats to MobModels */
DELETE FROM `MobModel_stats`;

INSERT INTO `MobModel_stats`(`object_id`, `index`, `value`) VALUES
       /* Charizard */
       ( 1,  0,   1),
       ( 1,  1,   2),
       ( 1,  2,   3),
       ( 1,  3,   4),
       ( 1,  4,   5),
       ( 1,  5,   6),
       ( 1,  6,   7),
       ( 1,  7,   8),
       /* Blastoise */
       ( 2,  0,   9),
       ( 2,  1,  10),
       ( 2,  2,  11),
       ( 2,  3,  12),
       ( 2,  4,  13),
       ( 2,  5,  14),
       ( 2,  6,  15),
       ( 2,  7,  16),
       /* Venusaur */
       ( 3,  0,  17),
       ( 3,  1,  18),
       ( 3,  2,  19),
       ( 3,  3,  20),
       ( 3,  4,  21),
       ( 3,  5,  22),
       ( 3,  6,  23),
       ( 3,  7,  24),
       /* Pikachu */
       ( 4,  0,  25),
       ( 4,  1,  26),
       ( 4,  2,  27),
       ( 4,  3,  28),
       ( 4,  4,  29),
       ( 4,  5,  30),
       ( 4,  6,  31),
       ( 4,  7,  32);

/* Inserting Mobs */
DELETE FROM `Mob`;

INSERT INTO `Mob`(`id`, `name`, `authKeys`, `currentExp`, `level`, `exp`, `model`) VALUES
       (1, 'TinyLezard',	2, 36435, 35, 40007, 1),
       (2, 'BigTurtle',		2,  2035, 15,  2535, 2),
       (3, 'VastFlowerPot',	2,  3120, 17,  3798, 3),
       (4, 'MegaFist',		2,  3120, 17,  3798, 1),
       (5, 'SuperWet',		2, 36435, 35, 40007, 2),
       (6, 'UltraBushy',	2,  2035, 15,  2535, 3),
       (7, 'Pikabillaud',	2,      0, 1,     1, 4),
       (8, 'Pikatheorie',	2,      0, 1,     1, 4);

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
       (2, 0, 1),
       (2, 1, 2),
       (2, 2, 3),
       (2, 3, 4);

/* Inserting Stuff */
DELETE FROM `Stuff`;

INSERT INTO `Stuff`(`id`, `name`, `stuffType`) VALUES
       (1, 'Coiffe Bouftou', 'HELMET'),
       (2, 'Cape Bouftou', 'CLOAK'),
       (3, 'Bottes Bouftou', 'BOOTS'),
       (4, 'Amulette Bouftou', 'NECKLACE'),
       (5, 'Epaulettes Bouftou', 'SHOULDERS'),
       (6, 'Plastron Bouftou', 'BREASTPLATE'),
       (7, 'Anneau Bouftou', 'RING'),
       (8, 'Ceinture Bouftou', 'BELT'),
       (9, 'Marteau Bouftou', 'WEAPON'),
       (10, 'Casque Piou', 'HELMET');

/* Inserting Stuff */
DELETE FROM `Stuff_stats`;

INSERT INTO `Stuff_stats`(`object_id`, `index`, `value`) VALUES
       (1, 0, 39),
       (1, 1, 40),
       (2, 0, 39),
       (2, 1, 41),
       (3, 0, 41),
       (3, 1, 42),
       (4, 0, 39),
       (4, 1, 44),
       (5, 0, 44),
       (5, 1, 40),
       (6, 0, 39),
       (6, 1, 41),
       (7, 0, 39),
       (7, 1, 44),
       (8, 0, 39),
       (8, 1, 40),
       (9, 0, 39),
       (9, 1, 40),
       (10, 0, 42),
       (10, 1, 40);

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

INSERT INTO `Player_stats`(`object_id`, `index`, `value`) VALUES
       (1, 0, 33),
       (1, 1, 34),
       (1, 2, 35),
       (2, 0, 36),
       (2, 1, 37),
       (2, 2, 38);

/* Inserting Ressources */
DELETE FROM `Ressource`;

INSERT INTO `Ressource`(`id`, `name`, `gather`, `level`, `exp`) VALUES
       (1, 'Orchidee',			1, 10, 100),
       (2, 'Peau de bouftou',		1,  1,  10),
       (3, 'Tree',			0,  0,   0),
       (4, 'Feuille de Venuzaur',	1,  0,   0),
       (5, 'Dent de Charizard',		1,  0,   0),
       (6, 'Ecaille de Blastoise',	1,  0,   0);

/* Inserting Heals */
DELETE FROM `Heal`;

INSERT INTO `Heal`(`id`, `name`, `pnjType`, `zone`, `x`, `y`) VALUES
       (1, 'Connard0', 'HEAL', 'Plain', 10, 70),
       (2, 'Connard1', 'HEAL', 'Plain', 30, 30),
       (3, 'Connard2', 'HEAL', 'Plain', 40, 40);

/* Inserting Consumable */
DELETE FROM `Consumable`;

INSERT INTO `Consumable`(`id`, `name`, `effectlib`) VALUES
       (1, 'Potion', 6),
       (2, 'Super Potion', 7);

/* Adding some fancy views because it's quite swag */
DROP VIEW IF EXISTS `StatView`;
CREATE VIEW StatView AS SELECT Stat.id, StatKey.name, Stat.value FROM Stat, StatKey WHERE Stat.key = StatKey.id;

DROP VIEW IF EXISTS `MobModelView`;
CREATE VIEW MobModelView AS 
       SELECT MobModel.id, MobModel.name AS model, Type.name AS type, StatView.name AS stat, StatView.value
       	      FROM StatView, Type, MobModel_stats, MobModel
       	      WHERE MobModel_stats.value = StatView.id
       	      	    AND MobModel_stats.object_id = MobModel.id
	     	    AND MobModel.type = Type.id;

DROP VIEW IF EXISTS `MobView`;
CREATE VIEW `MobView` AS
       SELECT Mob.id, Mob.name, Mob.level, MobModelView.model, MobModelView.type, MobModelView.stat, MobModelView.value AS modelValue, StatView.value AS mobValue
       	      FROM Mob, MobModelView, Mob_stats, StatView
       	      WHERE Mob.model = MobModelView.id
	      	    AND Mob_stats.object_id = Mob.id
	      	    AND StatView.id = Mob_stats.value
		    AND StatView.name = MobModelView.stat;

DROP VIEW IF EXISTS `PlayerView`;
CREATE VIEW `PlayerView` AS
       SELECT Player.id, Player.name, User.pseudo AS user, Faction.name AS faction, Player.level, Player.currentExp, DBZone.name AS zone, Player.x, Player.y,
       	      AuthorizedStatKeys.name AS statKeys, TalentTree.name AS talentTree, StatView.name AS stat, StatView.value
       	      FROM Player, Faction, User, DBZone, AuthorizedStatKeys, TalentTree, StatView, Player_stats
       	      WHERE Player.faction = Faction.id
       	      	    AND Player.user = User.id
	     	    AND Player.dbZone = DBZone.id
		    AND Player.authKeys = AuthorizedStatKeys.id
		    AND Player.talentTree = TalentTree.id
		    AND Player_stats.object_id = Player.id
		    AND Player_stats.value = StatView.id
	      ORDER BY Player.id;

DROP VIEW IF EXISTS `TypeView`;
CREATE VIEW `TypeView` AS
       SELECT Type.id, Type.name, OType.name AS other, Type_relations.value_coeff AS coeff
       	      FROM Type, Type AS OType, Type_relations
	      WHERE Type_relations.object_id = Type.id
	      	    AND Type_relations.value_oType_id = OType.id
	      ORDER BY Type.id, OType.id;

COMMIT;

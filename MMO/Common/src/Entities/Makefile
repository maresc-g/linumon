##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Mon Dec  2 13:08:08 2013 alexis mestag
## Last update Wed Mar 26 01:36:21 2014 alexis mestag
##

ENTITIES_SRC=		AEntity.cpp		\
			AItem.cpp		\
			AStatEntity.cpp		\
			ACharacter.cpp		\
			Carcass.cpp		\
			Cartridge.cpp		\
			CartridgeClip.cpp	\
			Consumable.cpp		\
			Craft.cpp		\
			DBZone.cpp		\
			Digitaliser.cpp		\
			Drop.cpp		\
			Equipment.cpp		\
			Faction.cpp		\
			Heal.cpp		\
			PNJ.cpp			\
			Inventory.cpp		\
			Job.cpp			\
			Gather.cpp		\
			Guild.cpp		\
			Jobs.cpp		\
			JobModel.cpp		\
			Levelable.cpp		\
			Mob.cpp			\
			MobModel.cpp		\
			Player.cpp		\
			Players.cpp		\
			Ressource.cpp		\
			Spell.cpp		\
			Spells.cpp		\
			Stack.cpp		\
			Stuff.cpp		\
			Type.cpp		\
			TypeRelations.cpp	\
			User.cpp

ENTITIES_SRC:=		$(addprefix $(ENTITIES)/, $(ENTITIES_SRC))

SRCCOMMON+=		$(ENTITIES_SRC)

ODB_ENTITIES+=		ACharacter.hh		\
			AStatEntity.hh		\
			Carcass.hh		\
			Consumable.hh		\
			Craft.hh		\
			DBZone.hh		\
			Faction.hh		\
			Heal.hh			\
			PNJ.hh			\
			Job.hh			\
			JobModel.hh		\
			Gather.hh		\
			Guild.hh		\
			Mob.hh			\
			MobModel.hh		\
			Player.hh		\
			Ressource.hh		\
			Spell.hh		\
			Stuff.hh		\
			Type.hh			\
			User.hh			\
			Views/UserView.hh	\
			Views/PlayerView.hh

ENTITIES_H_DIR=		$(subst src,include,$(ENTITIES))

ODB_ENTITIES_OPTIONS=	
ODB_ENTITIES_OPTIONS:=	$(addprefix $(ENTITIES_H_DIR)/, $(ODB_ENTITIES_OPTIONS))
ODB_OPTIONS+=		$(ODB_ENTITIES_OPTIONS)

ODB_ENTITIES:=		$(addprefix $(ENTITIES_H_DIR)/, $(ODB_ENTITIES))

ODB_CLASSES+=		$(ODB_ENTITIES)

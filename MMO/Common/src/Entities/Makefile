##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Mon Dec  2 13:08:08 2013 alexis mestag
## Last update Fri Feb 21 13:17:10 2014 laurent ansel
##

ENTITIES_SRC=		AEntity.cpp		\
			AItem.cpp		\
			AStatEntity.cpp		\
			ACharacter.cpp		\
			Consumable.cpp		\
			Craft.cpp		\
			DBZone.cpp		\
			Digitaliser.cpp		\
			Equipment.cpp		\
			Faction.cpp		\
			Heal.cpp		\
			Inventory.cpp		\
			Job.cpp			\
			Jobs.cpp		\
			JobModel.cpp		\
			Level.cpp		\
			Mob.cpp			\
			MobModel.cpp		\
			Player.cpp		\
			Players.cpp		\
			Ressource.cpp		\
			Ressources.cpp		\
			Spell.cpp		\
			Spells.cpp		\
			Stuff.cpp		\
			Type.cpp		\
			TypeRelations.cpp	\
			User.cpp

ENTITIES_SRC:=		$(addprefix $(ENTITIES)/, $(ENTITIES_SRC))

SRCCOMMON+=		$(ENTITIES_SRC)

ODB_ENTITIES+=		ACharacter.hh		\
			AEntity.hh		\
			AItem.hh		\
			AStatEntity.hh		\
			Craft.hh		\
			Consumable.hh		\
			DBZone.hh		\
			Digitaliser.hh		\
			Faction.hh		\
			Heal.hh			\
			Inventory.hh		\
			Job.hh			\
			JobModel.hh		\
			Level.hh		\
			Mob.hh			\
			MobModel.hh		\
			Player.hh		\
			Players.hh		\
			Ressource.hh		\
			Spell.hh		\
			Spells.hh		\
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

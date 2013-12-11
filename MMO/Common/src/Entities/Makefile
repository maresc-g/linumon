##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Mon Dec  2 13:08:08 2013 alexis mestag
## Last update Tue Dec 10 15:32:04 2013 alexis mestag
##

ENTITIES_SRC=		User.cpp		\
			AEntity.cpp		\
			AStatEntity.cpp		\
			ACharacter.cpp		\
			Player.cpp		\
			Players.cpp		\
			Mob.cpp			\
			Type.cpp		\
			Spell.cpp		\
			TypeRelations.cpp	\
			Faction.cpp		\
			Digitaliser.cpp

ENTITIES_SRC:=		$(addprefix $(ENTITIES)/, $(ENTITIES_SRC))

SRCCOMMON+=		$(ENTITIES_SRC)

ODB_ENTITIES+=		User.hh			\
			Player.hh		\
			Mob.hh			\
			ACharacter.hh		\
			AStatEntity.hh		\
			AEntity.hh		\
			Type.hh			\
			Spell.hh		\
			Faction.hh

ENTITIES_H_DIR=		$(subst src,include,$(ENTITIES))

ODB_ENTITIES_OPTIONS=	Players.options		\
			TypeRelations.options	\
			Digitaliser.options
ODB_ENTITIES_OPTIONS:=	$(addprefix $(ENTITIES_H_DIR)/, $(ODB_ENTITIES_OPTIONS))
ODB_OPTIONS+=		$(ODB_ENTITIES_OPTIONS)

ODB_ENTITIES:=		$(addprefix $(ENTITIES_H_DIR)/, $(ODB_ENTITIES))

ODB_CLASSES+=		$(ODB_ENTITIES)

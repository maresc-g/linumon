##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Thu Jan 30 13:56:42 2014 alexis mestag
## Last update Wed Feb 26 13:44:52 2014 alexis mestag
##

EFFECTS_SRC=		EffectLib.cpp			\
			FactionEffect.cpp		\
			MobEffect.cpp

EFFECTS_SRC:=		$(addprefix $(EFFECTS)/,$(EFFECTS_SRC))

SRCCOMMON+=		$(EFFECTS_SRC)

EFFECTS_H_DIR=		$(subst src,include,$(EFFECTS))

ODB_EFFECTS_OPTIONS=	
ODB_EFFECTS_OPTIONS:=	$(addprefix $(EFFECTS_H_DIR)/,$(ODB_EFFECTS_OPTIONS))
ODB_OPTIONS+=		$(ODB_EFFECTS_OPTIONS)

ODB_EFFECTS=		EffectLib.hh
ODB_EFFECTS:=		$(addprefix $(EFFECTS_H_DIR)/,$(ODB_EFFECTS))
ODB_CLASSES+=		$(ODB_EFFECTS)

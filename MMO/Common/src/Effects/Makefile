##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Thu Jan 30 13:56:42 2014 alexis mestag
## Last update Thu Feb 27 16:57:18 2014 alexis mestag
##

EFFECTS_SRC=		EffectLib.cpp			\
			FactionEffect.cpp		\
			MobEffect.cpp			\
			PlayerEffect.cpp		\
			SpellEffect.cpp

EFFECTS_SRC:=		$(addprefix $(EFFECTS)/,$(EFFECTS_SRC))

SRCCOMMON+=		$(EFFECTS_SRC)

EFFECTS_H_DIR=		$(subst src,include,$(EFFECTS))

ODB_EFFECTS_OPTIONS=	
ODB_EFFECTS_OPTIONS:=	$(addprefix $(EFFECTS_H_DIR)/,$(ODB_EFFECTS_OPTIONS))
ODB_OPTIONS+=		$(ODB_EFFECTS_OPTIONS)

ODB_EFFECTS=		EffectLib.hh
ODB_EFFECTS:=		$(addprefix $(EFFECTS_H_DIR)/,$(ODB_EFFECTS))
ODB_CLASSES+=		$(ODB_EFFECTS)

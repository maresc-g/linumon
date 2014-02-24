##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sun Feb 16 17:04:54 2014 alexis mestag
## Last update Mon Feb 24 14:08:07 2014 alexis mestag
##

EFFECT_CMN_DIR=		..
EFFECT_SRC_DIR=		Sources
EFFECT_OBJ_DIR=		Objects

EFFECT_SRC=		DamageEffect.cpp
EFFECT_SRC:=		$(addprefix $(EFFECT_SRC_DIR)/,$(EFFECT_SRC))
EFFECT_OBJ=		$(EFFECT_SRC:.cpp=.o)
EFFECT_OBJ:=		$(subst $(EFFECT_SRC_DIR),$(EFFECT_OBJ_DIR),$(EFFECT_OBJ))

EFFECT_CMN_SRC=		Common/src/Utility/Nameable.cpp		\
			Common/src/Utility/Id.cpp		\
			Common/src/Database/Persistent.cpp	\
			Common/src/Entities/ACharacter.cpp	\
			Common/src/Entities/AStatEntity.cpp	\
			Common/src/Entities/AEntity.cpp		\
			Common/src/Stats/Stats.cpp		\
			Common/src/Stats/AuthorizedStatKeys.cpp	\
			Common/src/Stats/Stat.cpp		\
			Common/src/Stats/StatKey.cpp

EFFECT_CMN_SRC:=	$(addprefix $(EFFECT_CMN_DIR)/,$(EFFECT_CMN_SRC))

EFFECT_CMN_OBJ=		$(EFFECT_CMN_SRC:.cpp=.o)
EFFECT_CMN_OBJ:=	$(subst $(EFFECT_CMN_DIR),$(EFFECT_OBJ_DIR),$(EFFECT_CMN_OBJ))

EFFECT_LIBS=		$(EFFECT_OBJ:.o=.so)
EFFECT_LIBS:=		$(subst $(EFFECT_OBJ_DIR)/,,$(EFFECT_LIBS))

CPPFLAGS=		-W -Wall -Wextra -fPIC -I ../Common/include -std=c++0x -g -D SERVER

$(EFFECT_OBJ_DIR)/%.o:	$(EFFECT_SRC_DIR)/%.cpp
			g++ $(CPPFLAGS) -c -o $@ $<

$(EFFECT_OBJ_DIR)/%.o:	$(EFFECT_CMN_DIR)/%.cpp
			@mkdir -p $(dir $@)
			g++ $(CPPFLAGS) -c -o $@ $<

%.so:			$(EFFECT_OBJ_DIR)/%.o $(EFFECT_CMN_OBJ)
			g++ -shared -o $@ $< $(EFFECT_CMN_OBJ)

all:			$(EFFECT_OBJ_DIR) $(EFFECT_CMN_DIR) $(EFFECT_CMN_OBJ) $(EFFECT_LIBS)

$(EFFECT_OBJ_DIR):
			mkdir -p $(EFFECT_OBJ_DIR)

$(EFFECT_CMN_DIR):
			mkdir -p $(EFFECT_CMN_DIR)

clean:
			rm -f $(EFFECT_OBJ)
			rm -f $(EFFECT_CMN_OBJ)

fclean:			clean
			rm -f $(EFFECT_LIBS)

re:			fclean all

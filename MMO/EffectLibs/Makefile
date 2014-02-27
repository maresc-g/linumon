##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sun Feb 16 17:04:54 2014 alexis mestag
## Last update Thu Feb 27 20:44:32 2014 alexis mestag
##

EFFECT_CMN_DIR=		..
EFFECT_SRC_DIR=		Sources
EFFECT_OBJ_DIR=		Objects

EFFECT_SRC=		HesodeEffect.cpp			\
			CelestiaEffect.cpp			\
			NormalEffect.cpp

EFFECT_SRC:=		$(addprefix $(EFFECT_SRC_DIR)/,$(EFFECT_SRC))

EFFECT_OBJ=		$(EFFECT_SRC:.cpp=.o)
EFFECT_OBJ:=		$(subst $(EFFECT_SRC_DIR),$(EFFECT_OBJ_DIR),$(EFFECT_OBJ))

EFFECT_CMN_SRC=		Common/src/Database/Persistent.cpp		\
			Common/src/Effects/FactionEffect.cpp		\
			Common/src/Effects/MobEffect.cpp		\
			Common/src/Effects/PlayerEffect.cpp		\
			Common/src/Effects/SpellEffect.cpp		\
			Common/src/Entities/ACharacter.cpp		\
			Common/src/Entities/AStatEntity.cpp		\
			Common/src/Entities/AEntity.cpp			\
			Common/src/Entities/Digitaliser.cpp		\
			Common/src/Entities/DBZone.cpp			\
			Common/src/Entities/Equipment.cpp		\
			Common/src/Entities/Faction.cpp			\
			Common/src/Entities/Job.cpp			\
			Common/src/Entities/Jobs.cpp			\
			Common/src/Entities/Level.cpp			\
			Common/src/Entities/Mob.cpp			\
			Common/src/Entities/MobModel.cpp		\
			Common/src/Entities/Player.cpp			\
			Common/src/Entities/Spell.cpp			\
			Common/src/Entities/Spells.cpp			\
			Common/src/Entities/Type.cpp			\
			Common/src/Entities/TypeRelations.cpp		\
			Common/src/Mutex/AMutex.cpp			\
			Common/src/Mutex/UnixMutex.cpp			\
			Common/src/Stats/AuthorizedStatKeys.cpp		\
			Common/src/Stats/Stat.cpp			\
			Common/src/Stats/Stats.cpp			\
			Common/src/Stats/StatKey.cpp			\
			Common/src/Utility/Nameable.cpp			\
			Common/src/Utility/Id.cpp			\
			Common/include/Database/Persistent-odb.cxx	\
			Common/include/Entities/Faction-odb.cxx		\
			Common/include/Entities/Digitaliser-odb.cxx	\
			Common/include/Entities/DBZone-odb.cxx		\
			Common/include/Entities/Equipment-odb.cxx	\
			Common/include/Entities/Job-odb.cxx		\
			Common/include/Entities/Jobs-odb.cxx		\
			Common/include/Entities/Level-odb.cxx		\
			Common/include/Entities/Mob-odb.cxx		\
			Common/include/Entities/MobModel-odb.cxx	\
			Common/include/Entities/Player-odb.cxx		\
			Common/include/Entities/Spell-odb.cxx		\
			Common/include/Entities/Spells-odb.cxx		\
			Common/include/Entities/Type-odb.cxx		\
			Common/include/Utility/Nameable-odb.cxx		\
			Common/include/Stats/Stat-odb.cxx		\
			Common/include/Stats/Stats-odb.cxx		\
			Common/include/Stats/StatKey-odb.cxx

EFFECT_CMN_SRC:=	$(addprefix $(EFFECT_CMN_DIR)/,$(EFFECT_CMN_SRC))

EFFECT_CMN_OBJ=		$(EFFECT_CMN_SRC:.cpp=.o)
EFFECT_CMN_OBJ:=	$(EFFECT_CMN_OBJ:.cxx=.o)
EFFECT_CMN_OBJ:=	$(subst $(EFFECT_CMN_DIR),$(EFFECT_OBJ_DIR),$(EFFECT_CMN_OBJ))

EFFECT_LIBS=		$(EFFECT_OBJ:.o=.so)
EFFECT_LIBS:=		$(subst $(EFFECT_OBJ_DIR)/,,$(EFFECT_LIBS))

CPPFLAGS=		-W -Wall -Wextra -fPIC -I ../Common/include -std=c++0x -g -D SERVER
LDFLAGS=		-L/usr/lib/odb -lodb-mysql -lodb

$(EFFECT_OBJ_DIR)/%.o:	$(EFFECT_SRC_DIR)/%.cpp
			g++ $(CPPFLAGS) -c -o $@ $<

$(EFFECT_OBJ_DIR)/%.o:	$(EFFECT_CMN_DIR)/%.cpp
			@mkdir -p $(dir $@)
			g++ $(CPPFLAGS) -c -o $@ $<
$(EFFECT_OBJ_DIR)/%.o:	$(EFFECT_CMN_DIR)/%.cxx
			@mkdir -p $(dir $@)
			g++ $(CPPFLAGS) -c -o $@ $<

%.so:			$(EFFECT_OBJ_DIR)/%.o $(EFFECT_CMN_OBJ)
			g++ -shared -o $@ $< $(EFFECT_CMN_OBJ) $(LDFLAGS)

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

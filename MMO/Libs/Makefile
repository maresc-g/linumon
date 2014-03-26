##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sun Feb 16 17:04:54 2014 alexis mestag
## Last update Wed Mar 26 09:12:08 2014 alexis mestag
##

LIBS_SRC_DIR=		Sources

EFFECT_DIR=		Effects
EFFECT_SRC=		HesodeEffect.cpp			\
			CelestiaEffect.cpp			\
			HealEffect.cpp				\
			HealTargetEffect.cpp			\
			AttiranceEffect.cpp			\
			ContreEffect.cpp			\
			NormalEffect.cpp			\
			PotionEffect.cpp			\
			SuperPotionEffect.cpp			\
			NormalCartridgeEffect.cpp		\
			SuperCartridgeEffect.cpp
EFFECT_SRC:=		$(addprefix $(EFFECT_DIR)/,$(EFFECT_SRC))

EXPFUNC_DIR=		ExperienceFunctions
EXPFUNC_SRC=		FastFunction.cpp			\
			MediumFunction.cpp			\
			ParabolicFunction.cpp			\
			SlowFunction.cpp			\
			JobFunction.cpp
EXPFUNC_SRC:=		$(addprefix $(EXPFUNC_DIR)/,$(EXPFUNC_SRC))

TALENT_DIR=		Talents
TALENT_SRC=		HP_TalentEffect.cpp			\
			Atk_TalentEffect.cpp			\
			Def_TalentEffect.cpp			\
			Heal_TalentEffect.cpp			\
			Heal_TalentEffect.cpp			\
			AtkFire_TalentEffect.cpp		\
			AtkElectric_TalentEffect.cpp		\
			DefRock_TalentEffect.cpp		\
			DefSteel_TalentEffect.cpp		\
			HealGrass_TalentEffect.cpp		\
			HealWater_TalentEffect.cpp		\
			Capture_TalentEffect.cpp		\
			BattleMob_TalentEffect.cpp		\
			BagCapacity_TalentEffect.cpp
TALENT_SRC:=		$(addprefix $(TALENT_DIR)/,$(TALENT_SRC))

LIBS_SRC=		$(EFFECT_SRC)				\
			$(EXPFUNC_SRC)				\
			$(TALENT_SRC)
LIBS_SRC:=		$(addprefix $(LIBS_SRC_DIR)/,$(LIBS_SRC))
LIBS_OBJ=		$(LIBS_SRC:.cpp=.o)
LIBS=			$(LIBS_OBJ:.o=.so)

FINAL_LIBS=		$(notdir $(LIBS))

CPPFLAGS=		-W -Wall -Wextra -fPIC -I ../Common/include -std=c++0x -g -D SERVER -D SERVER_COMPILATION
LDFLAGS=		

%.o:			%.cpp
			g++ $(CPPFLAGS) -c -o $@ $<
%.so:			%.o
			g++ -shared -o $@ $< $(LDFLAGS) && ln -fs $@ $(notdir $@)

all:			$(FINAL_LIBS)

$(FINAL_LIBS):		$(LIBS)

clean:
			rm -f $(LIBS_OBJ)

fclean:			clean
			rm -f $(FINAL_LIBS)
			rm -f $(LIBS)

re:			fclean all

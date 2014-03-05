##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sun Feb 16 17:04:54 2014 alexis mestag
## Last update Wed Mar  5 18:31:53 2014 alexis mestag
##

EFFECT_SRC_DIR=		Sources

EFFECT_SRC=		HesodeEffect.cpp			\
			CelestiaEffect.cpp			\
			NormalEffect.cpp			\
			PotionEffect.cpp			\
			SuperPotionEffect.cpp

EFFECT_SRC:=		$(addprefix $(EFFECT_SRC_DIR)/,$(EFFECT_SRC))

EFFECT_OBJ=		$(EFFECT_SRC:.cpp=.o)

EFFECT_LIBS=		$(EFFECT_OBJ:.o=.so)
EFFECT_LIBS:=		$(subst $(EFFECT_SRC_DIR)/,,$(EFFECT_LIBS))

CPPFLAGS=		-W -Wall -Wextra -fPIC -I ../Common/include -std=c++0x -g -D SERVER
LDFLAGS=		

$(EFFECT_SRC_DIR)/%.o:	$(EFFECT_SRC_DIR)/%.cpp
			g++ $(CPPFLAGS) -c -o $@ $<

%.so:			$(EFFECT_SRC_DIR)/%.o
			g++ -shared -o $@ $< $(LDFLAGS)

all:			$(EFFECT_LIBS)

clean:
			rm -f $(EFFECT_OBJ)

fclean:			clean
			rm -f $(EFFECT_LIBS)

re:			fclean all

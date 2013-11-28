##
## Makefile for  in /home/ansel_l/Documents/Rtype/rtype/Server
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Mon Oct 28 16:05:51 2013 laurent ansel
## Last update Mon Nov 25 23:04:42 2013 alexis mestag
##

NAME=			test

SRCCOMMON=		main.cpp
OBJ=			$(SRCCOMMON:.cpp=.o)

CPPFLAGS=		-W -Wall -Wextra -I include -std=c++0x
LDFLAGS=

SRCDIR=			src
include			$(SRCDIR)/Makefile

all:			$(NAME)

$(NAME):		$(OBJ)
			g++ -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

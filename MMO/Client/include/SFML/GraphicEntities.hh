//
// GraphicEntities.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 10 16:43:24 2014 cyril jourdain
// Last update Tue Feb 11 10:33:57 2014 cyril jourdain
//

#ifndef 		__GRAPHICENTITIES_HH__
# define 		__GRAPHICENTITIES_HH__

#include		"SFML/Sprite/Sprite.hh"
#include		"Entities/Player.hh"

struct GraphicPlayer
{
  Player	*_playerPtr;
  Animation	*_anim;
};

#endif

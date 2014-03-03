//
// Clickable.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Feb 28 13:50:28 2014 cyril jourdain
// Last update Fri Feb 28 19:02:45 2014 cyril jourdain
//

#include		"SFML/Clickable.hh"

Clickable::Clickable() :
  _pos(sf::Vector2f(0,0))
{
}

Clickable::~Clickable()
{
}

sf::Vector2f	const	*Clickable::getPos() const
{
  return &_pos;
}

void			Clickable::setPos(float x, float y)
{
  _pos.x = x; _pos.y = y;
}

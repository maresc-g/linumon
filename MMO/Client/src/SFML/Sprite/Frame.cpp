//
// Frame.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Mar 11 16:31:01 2014 cyril jourdain
// Last update Tue Mar 11 21:28:49 2014 cyril jourdain
//

#include		"SFML/Sprite/Frame.hh"

Frame::Frame(sf::IntRect const &sprite, sf::Vector2f const &offset) :
  _sprite(new sf::IntRect(sprite)), _offset(new sf::Vector2f(offset))
{
}

Frame::Frame(Frame const &other) :
  _sprite(new sf::IntRect(*other._sprite)), _offset(new sf::Vector2f(*other._offset))
{
}

Frame::~Frame()
{
  delete _sprite;
  delete _offset;
}

sf::IntRect		*Frame::getSpriteRect() const {return _sprite;}
sf::Vector2f		*Frame::getOffset() const {return _offset;}

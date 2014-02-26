//
// OPlayerSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Feb 25 14:25:26 2014 cyril jourdain
// Last update Tue Feb 25 16:04:31 2014 cyril jourdain
//

#include		"SFML/OPlayerSprite.hh"
#include		"Client.hh"

OPlayerSprite::OPlayerSprite(sf::String const &name, sf::Font * font) :
  PlayerSprite(name, font)
{
}

OPlayerSprite::~OPlayerSprite()
{
}

void			OPlayerSprite::moveUp(float px, sf::View *)
{
  play("up");
  move(0,-px);
  _deltaPos.y += px;
  // if (_deltaPos.y <= CASE_SIZE - 10 && !_receivedInput)
  //   _isInputable = false;
  // if (_deltaPos.y >= CASE_SIZE - 10 && !_receivedInput)
  //   _isInputable = true;
  // else if (_deltaPos.y >= CASE_SIZE - 10 && _receivedInput)
  //   _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE)
    {
      _pos.y -= 1;
      _deltaPos.y -= CASE_SIZE;
      _dir = NONE;
      move(0, _deltaPos.y);
      _deltaPos.y = 0;
      play("default_up");
    }
}

void			OPlayerSprite::moveDown(float px, sf::View *)
{
  play("down");
  move(0,px);
  _deltaPos.y += px;
  if (_deltaPos.y >= CASE_SIZE)
    {
      _pos.y += 1;
      _deltaPos.y -= CASE_SIZE;
      _dir = NONE;
      move(0, -_deltaPos.y);
      _deltaPos.y = 0;
      play("default_down");
    }
}

void			OPlayerSprite::moveLeft(float px, sf::View *)
{
  play("left");
  move(-px,0);
  _deltaPos.x += px;
  if (_deltaPos.x >= CASE_SIZE)
    {
      _pos.x -= 1;
      _deltaPos.x -= CASE_SIZE;
      _dir = NONE;
      move(_deltaPos.x, 0);
      _deltaPos.x= 0;
      play("default_left");
    }
}

void			OPlayerSprite::moveRight(float px, sf::View *)
{
  play("right");
  move(px,0);
  _deltaPos.x += px;
  if (_deltaPos.x >= CASE_SIZE)
    {
      _pos.x += 1;
      _deltaPos.x -= CASE_SIZE;
      _dir = NONE;
      move(-_deltaPos.x, 0);
      _deltaPos.x = 0;
      play("default_right");
    }
}
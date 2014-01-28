//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Mon Jan 27 12:36:28 2014 laurent ansel
//

#include			"Entities/Player.hh"

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL)
{

}

Player::Player(std::string const &name) :
  Persistent(), ACharacter(name, eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL)
{

}

Player::Player(Player const &rhs) :
  Persistent(rhs), ACharacter(rhs), _coord(new PlayerCoordinate)
{
  *this = rhs;
}

Player::~Player()
{
  delete _coord;
}

Player				&Player::operator=(Player const &rhs)
{
  if (this != &rhs)
    {
      this->setCoord(rhs.getCoord());
      this->setFaction(rhs.getFaction());
    }
  return (*this);
}

Player::PlayerCoordinate const		&Player::getCoord() const
{
  return (*_coord);
}

Player::PlayerCoordinate::type const	&Player::getX() const
{
  return (_coord->getX());
}

Player::PlayerCoordinate::type const	&Player::getY() const
{
  return (_coord->getY());
}

void				Player::setCoord(PlayerCoordinate const &coord)
{
  *_coord = coord;
}

void				Player::setCoord(PlayerCoordinate::type const &x,
						 PlayerCoordinate::type const &y)
{
  this->setX(x);
  this->setY(y);
}

void				Player::setX(PlayerCoordinate::type const &x)
{
  _coord->setX(x);
}

void				Player::setY(PlayerCoordinate::type const &y)
{
  _coord->setY(y);
}

Faction const			&Player::getFaction() const
{
  return (*_faction);
}

void				Player::setFaction(Faction const &faction)
{
  _faction = &faction;
}

Digitaliser const		&Player::getDigitaliser() const
{
  return (_digitaliser);
}

/*
** faction -> const, Why ?
*/

bool				Player::serialization(Trame &trame)
{
  bool				ret;

  if ((ret = this->_coord->serialization(*(static_cast<Trame *>(&trame[CONTENT]["PLAYER"])))))
    //    if ((ret = this->_faction->serialization(trame)))
    ret = this->_digitaliser.serialization(trame);
  return (ret);
}

bool				Player::deserialization(Trame const &trame)
{
  bool				ret;

  if (trame[CONTENT].isMember("PLAYER"))
    {
      //      if ((ret = this->_coord->deserialization(*(static_cast<Trame *>(&trame[CONTENT]["PLAYER"])))))
	//	if ((ret = this->_faction->deserialization(trame)))
	ret = this->_digitaliser.deserialization(trame);
    }
  return (ret);
}

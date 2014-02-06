//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Thu Feb  6 12:37:25 2014 laurent ansel
//

#include			<functional>
#include			"Entities/Player.hh"

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL), _zone(ZONE::eZone::NONE), _talentTree(NULL)
{

}

Player::Player(std::string const &name) :
  Persistent(), ACharacter(name, eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL), _zone(ZONE::eZone::NONE), _talentTree(NULL)
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
  this->deleteTalents();
  // delete _faction; // Causes an invalid pointer delete
}

Player				&Player::operator=(Player const &rhs)
{
  if (this != &rhs)
    {
      this->setCoord(rhs.getCoord());
      this->setFaction(rhs.getFaction());
      this->setZone(rhs.getZone());
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

bool				Player::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["PLAYER"]["NAME"] = this->getName();
  trame["PLAYER"]["TYPE"] = this->getStatEntityType();
  this->_coord->serialization(trame(trame["PLAYER"]));
  this->_faction->serialization(trame(trame["PLAYER"]));
  this->_digitaliser.serialization(trame(trame["PLAYER"]));
  this->getLevel().serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["CURRENTEXP"] = this->getCurrentExp();
  trame["PLAYER"]["ZONE"] = this->getZone();
  return (ret);
}

Player				*Player::deserialization(Trame const &trame)
{
  Player			*player = NULL;

  if (trame.isMember("PLAYER"))
    {
      player = new Player(trame["PLAYER"]["NAME"].asString());
      player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame["PLAYER"]["TYPE"].asInt()));
      player->setCoord(*PlayerCoordinate::deserialization(trame(trame["PLAYER"])));
      player->setFaction(*Faction::deserialization(trame(trame["PLAYER"])));
      player->setLevel(*Level::deserialization(trame(trame["PLAYER"])));
      player->setCurrentExp(trame["PLAYER"]["CURRENTEXP"].asInt());
      player->setZone(static_cast<ZONE::eZone>(trame["PLAYER"]["ZONE"].asInt()));
    }
  return (player);
}

ZONE::eZone			Player::getZone() const
{
  return (_zone);
}

void				Player::setZone(ZONE::eZone const zone)
{
  _zone = zone;
}

User const			&Player::getUser() const
{
  return (*this->_user);
}

void				Player::deleteTalents()
{
  static std::function<bool(Talent *)>	talentsDeleter = [](Talent *t) {
    delete t;
    return (true);
  };

  _talents.remove_if(talentsDeleter);
}

std::list<Talent *> const	&Player::getTalents() const
{
  return (_talents);
}

void				Player::capture(Mob const &mob)
{
  this->_digitaliser.addMob(mob);
}

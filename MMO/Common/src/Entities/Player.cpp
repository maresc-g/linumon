//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Mon Feb 10 15:19:34 2014 laurent ansel
//

#include			<functional>
#include			"Entities/Player.hh"

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL), _zone("NONE"), _talentTree(NULL)
{

}

Player::Player(std::string const &name) :
  Persistent(), ACharacter(name, eCharacter::PLAYER), _coord(new PlayerCoordinate),
  _faction(NULL), _zone("NONE"), _talentTree(NULL)
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

  trame["PLAYER"]["ID"] = static_cast<int>(this->getId());
  trame["PLAYER"]["NAME"] = this->getName();
  trame["PLAYER"]["TYPE"] = this->getStatEntityType();
  this->_coord->serialization(trame(trame["PLAYER"]));
  this->_faction->serialization(trame(trame["PLAYER"]));
  this->_digitaliser.serialization(trame(trame["PLAYER"]));
  this->getLevel().serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["CURRENTEXP"] = this->getCurrentExp();
  trame["PLAYER"]["ZONE"] = this->getZone();
  this->_talentTree->serialization(trame(trame["PLAYER"]));
  for (auto it = this->_talents.begin() ; it != this->_talents.end() ; ++it)
    (*it)->serialization(trame(trame["PLAYER"]["TALENTS"]));
  return (ret);
}

Player				*Player::deserialization(Trame const &trame)
{
  Player			*player = NULL;
  std::list<Talent *>		*talents = NULL;

  if (trame.isMember("PLAYER"))
    {
      player = new Player(trame["PLAYER"]["NAME"].asString());
      player->setId(trame["PLAYER"]["ID"].asUInt());
      player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame["PLAYER"]["TYPE"].asInt()));
      player->setCoord(*PlayerCoordinate::deserialization(trame(trame["PLAYER"])));
      player->setFaction(*Faction::deserialization(trame(trame["PLAYER"])));
      player->setLevel(*Level::deserialization(trame(trame["PLAYER"])));
      player->setCurrentExp(trame["PLAYER"]["CURRENTEXP"].asInt());
      player->setZone(trame["PLAYER"]["ZONE"].asString());
      player->setTalentTree(*TalentTree::deserialization(trame(trame["PLAYER"])));

      auto			members = trame["PLAYER"]["TALENTS"].getMemberNames();

      talents = new std::list<Talent *>;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	talents->push_back(Talent::deserialization(trame(trame["PLAYER"]["TALENTS"][*it])));
      player->setTalents(*talents);
    }
  return (player);
}

void				Player::addTalent(Talent *talent)
{
  this->_talents.push_back(talent);
}

void				Player::setTalentTree(TalentTree const &tree)
{
  this->_talentTree = &tree;
}

void				Player::setTalents(std::list<Talent *> const &list)
{
  this->_talents = list;
}

std::string			Player::getZone() const
{
  return (_zone);
}

void				Player::setZone(std::string const zone)
{
  _zone = zone;
}

User const			&Player::getUser() const
{
  return (*this->_user);
}

void				Player::setUser(User const &user)
{
  _user = &user;
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

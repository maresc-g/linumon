//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Tue Mar  4 00:59:24 2014 alexis mestag
//

#include			"Entities/Ressource.hh"

Ressource::Ressource() :
  Persistent(),
  AItem("", AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate),
  _level(new Level),
  _visible(true)
{
}

Ressource::Ressource(std::string const &name) :
  Persistent(),
  AItem(name, AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate),
  _level(new Level),
  _visible(true)
{

}

Ressource::Ressource(Ressource const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate),
  _level(new Level),
  _visible(true)
{
  *this = rhs;
}

Ressource::~Ressource()
{

}

Ressource			&Ressource::operator=(Ressource const &rhs)
{
  if (this != &rhs)
    {
      this->setName(rhs.getName());
      this->setItemType(rhs.getItemType());
      this->setEntityType(rhs.getEntityType());
      this->setLevelObject(rhs.getLevelObject());
      *this->_coord = rhs.getCoord();
      this->setVisible(rhs.isVisible());
    }
  return (*this);
}

Ressource::RessourceCoordinate const	&Ressource::getCoord() const
{
  return (*this->_coord);
}

void				Ressource::setCoord(RessourceCoordinate const &coord)
{
  *_coord = coord;
}

void				Ressource::setLevelObject(Level const &level)
{
  *_level = level;
}

Level const			&Ressource::getLevelObject() const
{
  return (*this->_level);
}

Level::type			Ressource::getLevel() const
{
  return (_level->getLevel());
}

void				Ressource::setLevel(Level::type const level)
{
  return (_level->setLevel(level));
}

Level::type			Ressource::getExp() const
{
  return (_level->getExp());
}

void				Ressource::setExp(Level::type const exp)
{
  return (_level->setExp(exp));
}

Ressource::RessourceCoordinate::type const	&Ressource::getX() const
{
  return (this->_coord->getX());
}

Ressource::RessourceCoordinate::type const	&Ressource::getY() const
{
  return (this->_coord->getY());
}

void				Ressource::setX(RessourceCoordinate::type const &x)
{
  this->_coord->setX(x);
}

void				Ressource::setY(RessourceCoordinate::type const &y)
{
  this->_coord->setY(y);
}

bool				Ressource::isVisible() const
{
  return (this->_visible);
}


void				Ressource::setVisible(bool const visible)
{
  this->_visible = visible;
}

bool				Ressource::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getItemType();
  trame["EN"] = this->getEntityType();
  trame["VIS"] = this->isVisible();
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->_coord->serialization(trame);
  return (true);
}

Ressource			*Ressource::deserialization(Trame const &trame, bool const client)
{
  Ressource			*ressource = NULL;

  if (trame["TYPE"].asInt() == AItem::eItem::RESSOURCE || trame["EN"].asInt() == AEntity::eEntity::RESSOURCE || trame["EN"].asInt() == AEntity::eEntity::ITEM)
    {
      ressource = new Ressource(trame["NAME"].asString());
      if (client)
	ressource->setId(trame["ID"].asUInt());
      ressource->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
      ressource->setEntityType(static_cast<AEntity::eEntity>(trame["EN"].asInt()));
      if (trame.isMember("COORDINATE"))
	ressource->setCoord(*RessourceCoordinate::deserialization(trame(trame)));
      if (trame.isMember("VIS"))
      ressource->setVisible(trame["VIS"].asBool());
    }
  return (ressource);
}

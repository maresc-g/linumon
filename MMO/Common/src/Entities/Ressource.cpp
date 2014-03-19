//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Tue Mar 18 23:50:55 2014 alexis mestag
//

#include			"Entities/Ressource.hh"

Ressource::Ressource() :
  Persistent(),
  AItem("", AItem::eItem::RESSOURCE, AEntity::eEntity::RESSOURCE),
  _coord(new RessourceCoordinate),
  _level(0),
  _exp(0),
  _visible(true),
  _gather(false)
{
}

Ressource::Ressource(std::string const &name) :
  Persistent(),
  AItem(name, AItem::eItem::RESSOURCE, AEntity::eEntity::RESSOURCE),
  _coord(new RessourceCoordinate),
  _level(0),
  _exp(0),
  _visible(true),
  _gather(false)
{

}

Ressource::Ressource(Ressource const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::RESSOURCE, AEntity::eEntity::RESSOURCE),
  _coord(new RessourceCoordinate),
  _visible(true),
  _gather(false)
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
      this->setLevel(rhs.getLevel());
      this->setExp(rhs.getExp());
      *this->_coord = rhs.getCoord();
      this->setVisible(rhs.isVisible());
      this->setGather(rhs.isGather());
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

Levelable::type			Ressource::getLevel() const
{
  return (_level);
}

void				Ressource::setLevel(Levelable::type const level)
{
  _level = level;
}

Levelable::type			Ressource::getExp() const
{
  return (_exp);
}

void				Ressource::setExp(Levelable::type const exp)
{
  _exp = exp;
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

bool				Ressource::isGather() const
{
  return (this->_gather);
}


void				Ressource::setGather(bool const gather)
{
  this->_gather = gather;
}

bool				Ressource::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getItemType();
  trame["EN"] = this->getEntityType();
  trame["VIS"] = this->isVisible();
  trame["GAT"] = this->isGather();
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
      if (trame.isMember("GAT"))
	ressource->setGather(trame["GAT"].asBool());
    }
  return (ressource);
}

//
// Heal.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 21 13:05:16 2014 laurent ansel
// Last update Tue Feb 25 13:33:55 2014 laurent ansel
//

#include			"Entities/Heal.hh"

Heal::Heal() :
  AEntity("HEAL", eEntity::HEAL),
  _coord(NULL)
{

}

Heal::Heal(Heal const &rhs) :
  AEntity(rhs),
  _coord(NULL)
{
  *this = rhs;
}

Heal::~Heal()
{

}

Heal				&Heal::operator=(Heal const &rhs)
{
  if (this != &rhs)
    {
      this->setCoord(rhs.getCoord());
    }
  return (*this);
}

Heal::HealCoordinate const	&Heal::getCoord() const
{
  return (*this->_coord);
}

void				Heal::setCoord(Heal::HealCoordinate const &coord)
{
  *this->_coord = coord;
}

Heal::HealCoordinate::type const	&Heal::getX() const
{
  return (this->_coord->getX());
}

Heal::HealCoordinate::type const	&Heal::getY() const
{
  return (this->_coord->getY());
}

void				Heal::setX(Heal::HealCoordinate::type const &x)
{
  this->_coord->setX(x);
}

void				Heal::setY(Heal::HealCoordinate::type const &y)
{
  this->_coord->setY(y);
}

void				Heal::heal(Digitaliser const &) const
{

}

bool				Heal::serialization(Trame &trame) const
{
  trame["HEAL"]["TYPE"] = this->getEntityType();
  trame["HEAL"]["NAME"] = this->getName();
  trame["HEAL"]["ID"] = static_cast<unsigned int>(this->getId());
  this->_coord->serialization(trame(trame["HEAL"]));
  return (true);
}

Heal				*Heal::deserialization(Trame const &trame)
{
  Heal				*heal = NULL;

  if (trame.isMember("HEAL"))
    {
      heal = new Heal();
      heal->setName(trame["HEAL"]["NAME"].asString());
      heal->setId(trame["HEAL"]["ID"].asUInt());
      heal->setEntityType(static_cast<AEntity::eEntity>(trame["HEAL"]["TYPE"].asInt()));
      heal->setCoord(*HealCoordinate::deserialization(trame(trame["HEAL"])));
    }
  return (heal);
}

//
// Carcass.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar 14 11:04:13 2014 laurent ansel
// Last update Sat Mar 15 00:20:14 2014 alexis mestag
//

#include			"Entities/Carcass.hh"


Carcass::Carcass() :
  AEntity("", eEntity::CARCASS),
  ContainerWrapper<container_type>(),
  _coord(new CarcassCoordinate)
{
}

Carcass::Carcass(std::string const &name) :
  AEntity(name, eEntity::CARCASS),
  ContainerWrapper<container_type>(),
  _coord(new CarcassCoordinate)
{

}

Carcass::Carcass(Carcass const &rhs) :
  AEntity(rhs.getName(), eEntity::CARCASS),
  ContainerWrapper<container_type>(),
  _coord(new CarcassCoordinate)
{
  *this = rhs;
}

Carcass::~Carcass()
{
  delete _coord;
}

Carcass			&Carcass::operator=(Carcass const &rhs)
{
  if (this != &rhs)
    {
      this->setName(rhs.getName());
      this->setEntityType(rhs.getEntityType());
      *this->_coord = rhs.getCoord();
      this->setContainer(rhs.getContainer());
    }
  return (*this);
}

Carcass::CarcassCoordinate const	&Carcass::getCoord() const
{
  return (*this->_coord);
}

void				Carcass::setCoord(CarcassCoordinate const &coord)
{
  *_coord = coord;
}

Carcass::CarcassCoordinate::type const	&Carcass::getX() const
{
  return (this->_coord->getX());
}

Carcass::CarcassCoordinate::type const	&Carcass::getY() const
{
  return (this->_coord->getY());
}

void				Carcass::setX(CarcassCoordinate::type const &x)
{
  this->_coord->setX(x);
}

void				Carcass::setY(CarcassCoordinate::type const &y)
{
  this->_coord->setY(y);
}

bool				Carcass::serialization(Trame &trame) const
{
  trame["EN"] = this->getEntityType();
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->_coord->serialization(trame);
  return (true);
}

Carcass				*Carcass::deserialization(Trame const &trame)
{
  Carcass			*carcass = NULL;

  if (trame["EN"].asInt() == AEntity::eEntity::CARCASS)
    {
      carcass = new Carcass(trame["NAME"].asString());
      carcass->setId(trame["ID"].asUInt());
      carcass->setEntityType(static_cast<AEntity::eEntity>(trame["EN"].asInt()));
      if (trame.isMember("COORDINATE"))
	carcass->setCoord(*CarcassCoordinate::deserialization(trame(trame)));
    }
  return (carcass);
}

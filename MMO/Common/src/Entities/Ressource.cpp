//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Mon Feb 24 19:50:55 2014 laurent ansel
//

#include			"Entities/Ressource.hh"

Ressource::Ressource() :
  Persistent(),
  AItem("", AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate)
{

}

Ressource::Ressource(std::string const &name) :
  Persistent(),
  AItem(name, AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate)
{

}

Ressource::Ressource(Ressource const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::RESSOURCE),
  _coord(new RessourceCoordinate)
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
      this->setLevel(rhs.getLevel());
      *this->_coord = rhs.getCoord();
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

void				Ressource::setLevel(Level const &level)
{
  _level = level;
}

Level const			&Ressource::getLevel() const
{
  return (this->_level);
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

bool				Ressource::serialization(Trame &trame) const
{
  trame["RESSOURCE"]["TYPE"] = this->getItemType();
  trame["RESSOURCE"]["NAME"] = this->getName();
  trame["RESSOURCE"]["ID"] = static_cast<unsigned int>(this->getId());
  this->_coord->serialization(trame(trame["RESSOURCE"]));
  return (true);
}

Ressource			*Ressource::deserialization(Trame const &trame, bool const client)
{
  Ressource			*ressource = NULL;

  if (trame.isMember("RESSOURCE"))
    {
      ressource = new Ressource(trame["RESSOURCE"]["NAME"].asString());
      if (client)
	ressource->setId(trame["RESSOURCE"]["ID"].asUInt());
      ressource->setItemType(static_cast<AItem::eItem>(trame["RESSOURCE"]["TYPE"].asInt()));
      ressource->setCoord(*RessourceCoordinate::deserialization(trame(trame["RESSOURCE"])));
    }
  return (ressource);
}

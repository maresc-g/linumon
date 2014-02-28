//
// Gather.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:06 2014 laurent ansel
// Last update Fri Feb 28 15:32:00 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Gather.hh"

Gather::Gather():
  _ressource(NULL)
{
}

Gather::~Gather()
{
}

Gather::Gather(Gather const &rhs)
{
  *this = rhs;
}

Gather				&Gather::operator=(Gather const &rhs)
{
  if (this != &rhs)
    {
      this->setLevel(rhs.getLevel());
      this->setRessource(rhs.getRessource());
    }
  return (*this);
}

Level const			&Gather::getLevel() const
{
  return (this->_level);
}

void				Gather::setLevel(Level const &level)
{
  this->_level = level;
}

Ressource const			&Gather::getRessource() const
{
  return (*this->_ressource);
}

void				Gather::setRessource(Ressource const &ressource)
{
  this->_ressource = &ressource;
}

bool				Gather::serialization(Trame &trame) const
{
  bool				ret = true;

  this->_level.serialization(trame(trame));
  this->_ressource->serialization(trame(trame["RES"]));
  trame["RES"].removeMember("COORDINATE");
  trame["RES"].removeMember("VIS");
  return (ret);
}

Gather				*Gather::deserialization(Trame const &trame, bool const client)
{
  Gather			*gather = NULL;
  Ressource			*item;

  gather = new Gather;
  gather->setLevel(*Level::deserialization(trame(trame)));
  item = Ressource::deserialization(trame(trame["RES"]), client);
  gather->setRessource(*item);
  return (gather);
}

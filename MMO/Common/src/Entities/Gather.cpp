//
// Gather.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:06 2014 laurent ansel
// Last update Thu Mar  6 17:17:49 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Gather.hh"
#include			"Loader/LoaderManager.hh"

Gather::Gather():
  _level(new Level), _ressource(NULL)
{
}

Gather::~Gather()
{
  delete _level;
}

Gather::Gather(Gather const &rhs) :
  _level(new Level)
{
  *this = rhs;
}

Gather				&Gather::operator=(Gather const &rhs)
{
  if (this != &rhs)
    {
      this->setLevelObject(rhs.getLevelObject());
      this->setRessource(rhs.getRessource());
    }
  return (*this);
}

Level const			&Gather::getLevelObject() const
{
  return (*this->_level);
}

void				Gather::setLevelObject(Level const &level)
{
  *this->_level = level;
}

Ressource const			&Gather::getRessource() const
{
  return (*this->_ressource);
}

void				Gather::setRessource(Ressource const &ressource)
{
  this->_ressource = &ressource;
}

Level::type			Gather::getLevel() const
{
  return (_level->getLevel());
}

void				Gather::setLevel(Level::type const level)
{
  _level->setLevel(level);
}

Level::type			Gather::getExp() const
{
  return (_level->getExp());
}

void				Gather::setExp(Level::type const exp)
{
  _level->setExp(exp);
}

bool				Gather::serialization(Trame &trame) const
{
  bool				ret = true;

  this->_level->serialization(trame(trame));
  // this->_ressource->serialization(trame(trame["RES"]));
  // trame["RES"].removeMember("COORDINATE");
  // trame["RES"].removeMember("VIS");
  trame["RES"] = this->_ressource->getName();
  return (ret);
}

Gather				*Gather::deserialization(Trame const &trame, bool const)
{
  Gather			*gather = NULL;
  Ressource			*item;

  gather = new Gather;
  gather->setLevelObject(*Level::deserialization(trame(trame)));
  // item = Ressource::deserialization(trame(trame["RES"]), client);
  item = (**LoaderManager::getInstance()->getRessourceLoader())->getValue(trame["RES"].asString());
  if (item)
    gather->setRessource(*item);
  return (gather);
}

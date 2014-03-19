//
// Gather.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:06 2014 laurent ansel
// Last update Tue Mar 18 23:57:31 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Gather.hh"
#include			"Loader/LoaderManager.hh"

Gather::Gather():
  _level(0), _exp(0), _ressource(NULL)
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
      this->setExp(rhs.getExp());
      this->setRessource(rhs.getRessource());
    }
  return (*this);
}

Ressource const			&Gather::getRessource() const
{
  return (*this->_ressource);
}

void				Gather::setRessource(Ressource const &ressource)
{
  this->_ressource = &ressource;
}

Levelable::type			Gather::getLevel() const
{
  return (_level);
}

void				Gather::setLevel(Levelable::type const level)
{
  _level = level;
}

Levelable::type			Gather::getExp() const
{
  return (_exp);
}

void				Gather::setExp(Levelable::type const exp)
{
  _exp = exp;
}

bool				Gather::serialization(Trame &trame) const
{
  bool				ret = true;

  // this->_level->serialization(trame(trame));
  trame["LVL"] = this->getLevel();
  trame["EXP"] = this->getExp();
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
  // gather->setLevelObject(*Level::deserialization(trame(trame)));
  gather->setLevel(trame["LVL"].asUInt());
  gather->setExp(trame["EXP"].asUInt());
  // item = Ressource::deserialization(trame(trame["RES"]), client);
  item = (**LoaderManager::getInstance()->getRessourceLoader())->getValue(trame["RES"].asString());
  if (item)
    gather->setRessource(*item);
  return (gather);
}

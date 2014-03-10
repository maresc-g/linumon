//
// HealLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar  7 14:18:07 2014 laurent ansel
// Last update Mon Mar 10 14:01:43 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
#include			"Entities/Heal-odb.hxx"
#endif
#include			"Database/Repositories/Repository.hpp"
#include			"Loader/HealLoader.hh"
#include			"Map/Map.hh"

/*
**
**	Heals
**
*/

Heals::Heals() :
  _heals(new std::list<Heal *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Heal>		*mm = &Database::getRepository<Heal>();

  *_heals = mm->getAll();
  for (auto it = _heals->begin() ; it != _heals->end() ; ++it)
    Map::getInstance()->addEntity((*it)->getZone(), *it);
#endif
}

Heals::~Heals()
{
  for (auto it = _heals->begin() ; it != _heals->end() ; ++it)
    delete *it;
  delete _heals;
}

std::list<Heal *> const		&Heals::getHeals() const
{
  return (*this->_heals);
}

void				Heals::addHeal(Heal *heal)
{
  this->_heals->push_back(heal);
}

Heal				*Heals::getHeal(std::string const &name) const
{
  for (auto it = _heals->begin() ; it != _heals->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Heal				*Heals::getHeal(unsigned int const id) const
{
  for (auto it = _heals->begin() ; it != _heals->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	HealLoader
**
*/

HealLoader::HealLoader() :
  _heals(new Heals)
{

}

HealLoader::~HealLoader()
{
  delete _heals;
}

bool				HealLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["HEALS"];
  for (auto it = _heals->getHeals().begin() ; it != _heals->getHeals().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["HEALS"][(*it)->getName()]));
  return (ret);
}

bool				HealLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Heal			*heal;

  if (trame[CONTENT].isMember("HEALS"))
    {
      auto			members = trame[CONTENT]["HEALS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  heal = Heal::deserialization(trame(trame[CONTENT]["HEALS"][*it]));
	  if (heal)
	    {
	      heal->setName(*it);
	      _heals->addHeal(heal);
	    }
	}
    }
  return (ret);
}

Heals const			&HealLoader::getLoaderContent() const
{
  return (*_heals);
}

Heals::value			*HealLoader::getValue(std::string const &name) const
{
  return (this->_heals->getHeal(name));
}

Heals::value			*HealLoader::getValue(unsigned int const id) const
{
  return (this->_heals->getHeal(id));
}

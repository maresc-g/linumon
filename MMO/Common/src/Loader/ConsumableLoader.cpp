//
// ConsumableLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 11:54:34 2014 laurent ansel
// Last update Fri Mar 14 15:03:25 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
# include			"Entities/Consumable-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/ConsumableLoader.hh"

/*
**
**	Consumables
**
*/

Consumables::Consumables() :
  _consumables(new std::list<Consumable *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Consumable>		*mm = &Database::getRepository<Consumable>();

  *_consumables = mm->getAll();
#endif
}

Consumables::~Consumables()
{
  for (auto it = _consumables->begin() ; it != _consumables->end() ; ++it)
    delete *it;
  delete _consumables;
}

std::list<Consumable *> const	&Consumables::getConsumables() const
{
  return (*this->_consumables);
}

void				Consumables::addConsumable(Consumable *consumable)
{
  this->_consumables->push_back(consumable);
}

Consumable				*Consumables::getConsumable(std::string const &name) const
{
  for (auto it = _consumables->begin() ; it != _consumables->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Consumable				*Consumables::getConsumable(unsigned int const id) const
{
  for (auto it = _consumables->begin() ; it != _consumables->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	ConsumableLoader
**
*/

ConsumableLoader::ConsumableLoader() :
  _consumables(new Consumables)
{

}

ConsumableLoader::~ConsumableLoader()
{
  delete _consumables;
}

bool				ConsumableLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["CONSUMABLES"];
  for (auto it = _consumables->getConsumables().begin() ; it != _consumables->getConsumables().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["CONSUMABLES"][(*it)->getName()]));
  return (ret);
}

bool				ConsumableLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Consumable			*consumable;

  if (trame[CONTENT].isMember("CONSUMABLES"))
    {
      auto			members = trame[CONTENT]["CONSUMABLES"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  consumable = Consumable::deserialization(trame(trame[CONTENT]["CONSUMABLES"][*it]));
	  if (consumable)
	    {
	      consumable->setName(*it);
	      _consumables->addConsumable(consumable);
	    }
	}
    }
  return (ret);
}

Consumables const			&ConsumableLoader::getLoaderContent() const
{
  return (*_consumables);
}

Consumables::value			*ConsumableLoader::getValue(std::string const &name) const
{
  return (this->_consumables->getConsumable(name));
}

Consumables::value			*ConsumableLoader::getValue(unsigned int const id) const
{
  return (this->_consumables->getConsumable(id));
}

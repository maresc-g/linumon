//
// StuffManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 11:09:09 2014 laurent ansel
// Last update Thu Mar  6 13:38:29 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
#include			"Entities/Stuff-odb.hxx"
#endif
#include			"Database/Repositories/Repository.hpp"
#include			"Loader/StuffLoader.hh"

/*
**
**	Stuffs
**
*/

Stuffs::Stuffs() :
  _stuffs(new std::list<Stuff *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Stuff>		*mm = &Database::getRepository<Stuff>();

  *_stuffs = mm->getAll();
#endif
}

Stuffs::~Stuffs()
{
  for (auto it = _stuffs->begin() ; it != _stuffs->end() ; ++it)
    delete *it;
  delete _stuffs;
}

std::list<Stuff *> const	&Stuffs::getStuffs() const
{
  return (*this->_stuffs);
}

void				Stuffs::addStuff(Stuff *stuff)
{
  this->_stuffs->push_back(stuff);
}

Stuff				*Stuffs::getStuff(std::string const &name) const
{
  for (auto it = _stuffs->begin() ; it != _stuffs->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Stuff				*Stuffs::getStuff(unsigned int const id) const
{
  for (auto it = _stuffs->begin() ; it != _stuffs->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	StuffLoader
**
*/

StuffLoader::StuffLoader() :
  _stuffs(new Stuffs)
{

}

StuffLoader::~StuffLoader()
{
  delete _stuffs;
}

bool				StuffLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["STUFFS"];
  for (auto it = _stuffs->getStuffs().begin() ; it != _stuffs->getStuffs().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["STUFFS"][(*it)->getName()]));
  return (ret);
}

bool				StuffLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Stuff			*stuff;

  if (trame[CONTENT].isMember("STUFFS"))
    {
      auto			members = trame[CONTENT]["STUFFS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  stuff = Stuff::deserialization(trame(trame[CONTENT]["STUFFS"][*it]));
	  if (stuff)
	    {
	      stuff->setName(*it);
	      _stuffs->addStuff(stuff);
	    }
	}
    }
  return (ret);
}

Stuffs const			&StuffLoader::getLoaderContent() const
{
  return (*_stuffs);
}

Stuffs::value			*StuffLoader::getValue(std::string const &name) const
{
  return (this->_stuffs->getStuff(name));
}

Stuffs::value			*StuffLoader::getValue(unsigned int const id) const
{
  return (this->_stuffs->getStuff(id));
}

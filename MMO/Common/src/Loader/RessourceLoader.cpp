//
// RessourceLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 13:16:43 2014 laurent ansel
// Last update Thu Mar  6 16:56:17 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
#include			"Entities/Ressource-odb.hxx"
#endif
#include			"Database/Repositories/Repository.hpp"
#include			"Loader/RessourceLoader.hh"

/*
**
**	Ressources
**
*/

Ressources::Ressources() :
  _ressources(new std::list<Ressource *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Ressource>		*mm = &Database::getRepository<Ressource>();

  *_ressources = mm->getAll();
#endif
}

Ressources::~Ressources()
{
  for (auto it = _ressources->begin() ; it != _ressources->end() ; ++it)
    delete *it;
  delete _ressources;
}

std::list<Ressource *> const	&Ressources::getRessources() const
{
  return (*this->_ressources);
}

void				Ressources::addRessource(Ressource *ressource)
{
  this->_ressources->push_back(ressource);
}

Ressource			*Ressources::getRessource(std::string const &name) const
{
  for (auto it = _ressources->begin() ; it != _ressources->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Ressource			*Ressources::getRessource(unsigned int const id) const
{
  for (auto it = _ressources->begin() ; it != _ressources->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	RessourceLoader
**
*/

RessourceLoader::RessourceLoader() :
  _ressources(new Ressources)
{

}

RessourceLoader::~RessourceLoader()
{
  delete _ressources;
}

bool				RessourceLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["RESSOURCES"];
  for (auto it = _ressources->getRessources().begin() ; it != _ressources->getRessources().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["RESSOURCES"][(*it)->getName()]));
  return (ret);
}

bool				RessourceLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Ressource			*ressource;

  if (trame[CONTENT].isMember("RESSOURCES"))
    {
      auto			members = trame[CONTENT]["RESSOURCES"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  ressource = Ressource::deserialization(trame(trame[CONTENT]["RESSOURCES"][*it]));
	  if (ressource)
	    {
	      ressource->setName(*it);
	      _ressources->addRessource(ressource);
	    }
	}
    }
  return (ret);
}

Ressources const		&RessourceLoader::getLoaderContent() const
{
  return (*_ressources);
}

Ressources::value		*RessourceLoader::getValue(std::string const &name) const
{
  return (this->_ressources->getRessource(name));
}

Ressources::value		*RessourceLoader::getValue(unsigned int const id) const
{
  return (this->_ressources->getRessource(id));
}

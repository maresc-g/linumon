//
// Ressources.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 18 14:46:08 2014 laurent ansel
// Last update Wed Mar  5 14:41:13 2014 laurent ansel
//

#include			"Database/Repositories/Repository.hpp"
#include			"Database/Loaders/RessourceLoader.hh"

RessourceLoader::RessourceLoader() :
  Singleton<RessourceLoader>()
{
  Repository<Ressource>		*rr = &Database::getRepository<Ressource>();

  _ressources = rr->getAll();
}

RessourceLoader::RessourceLoader(RessourceLoader const &rhs) :
  Singleton<RessourceLoader>()
{
  *this = rhs;
}

RessourceLoader::~RessourceLoader()
{

}

RessourceLoader			&RessourceLoader::operator=(RessourceLoader const &rhs)
{
  if (this != &rhs)
    {
      this->setRessources(rhs.getRessources());
    }
  return (*this);
}

Ressource const			*RessourceLoader::operator[](std::string const &name) const
{
  return (this->getRessource(name));
}

void				RessourceLoader::setRessources(container_type const &ressources)
{
  _ressources = ressources;
}


RessourceLoader::container_type const	&RessourceLoader::getRessources() const
{
  return (_ressources);
}

Ressource const			*RessourceLoader::getRessource(std::string const &name) const
{
  for (auto it = _ressources.begin() ; it != _ressources.end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}


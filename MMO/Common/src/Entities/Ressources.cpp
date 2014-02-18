//
// Ressources.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 18 14:46:08 2014 laurent ansel
// Last update Tue Feb 18 14:55:58 2014 laurent ansel
//

#include			"Entities/Ressources.hh"


Ressources::Ressources()
{

}

Ressources::Ressources(Ressources const &rhs)
{
  *this = rhs;
}

Ressources::~Ressources()
{

}

Ressources			&Ressources::operator=(Ressources const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

void				Ressources::setRessources(std::list<Ressource *> const &ressources)
{
  _ressources = ressources;
}


std::list<Ressource *> const	&Ressources::getRessources() const
{
  return (_ressources);
}

Ressource 			*Ressources::getRessource(std::string const &name) const
{
  for (auto it = _ressources.begin() ; it != _ressources.end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}


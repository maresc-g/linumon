//
// Faction.cpp for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:31:07 2013 alexis mestag
// Last update Thu Nov 28 23:40:28 2013 alexis mestag
//

#include			"Entities/Faction.hh"

Faction::Faction(std::string const &name) :
  AStatEntity(name)
{

}

Faction::Faction(Faction const &rhs) :
  AStatEntity(rhs)
{

}

Faction::~Faction()
{

}

Faction				&Faction::operator=(Faction const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

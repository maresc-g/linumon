//
// Faction.cpp for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:31:07 2013 alexis mestag
// Last update Thu Jan 30 16:25:35 2014 laurent ansel
//

#include			"Entities/Faction.hh"

Faction::Faction(std::string const &name) :
  Persistent(), Nameable(name)
{

}

Faction::Faction(Faction const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
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

bool				Faction::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["FACTION"] = this->getName();
  return (ret);
}

Faction				*Faction::deserialization(Trame const &trame)
{
  Faction			*faction = NULL;

  if (trame.isMember("FACTION"))
    faction = new Faction(trame["FACTION"].asString());
  return (faction);
}

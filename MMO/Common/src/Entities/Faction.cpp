//
// Faction.cpp for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:31:07 2013 alexis mestag
// Last update Mon Jan 27 13:08:00 2014 laurent ansel
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

bool				Faction::serialization(Trame &) const
{
  bool				ret = true;

  //  trame[CONTENT]["PLAYER"]["FACTION"] = this->_name;
  return (ret);
}

bool				Faction::deserialization(Trame const &)
{
  bool				ret = true;;

  //  if (trame[CONTENT]["PLAYER"].isMember("FACTION"))
    //this->_name = trame[CONTENT]["PLAYER"]["FACTION"].asString();
  return (ret);

}

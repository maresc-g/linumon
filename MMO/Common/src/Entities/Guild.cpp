//
// Guild.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 12:43:18 2014 laurent ansel
// Last update Tue Feb 25 12:43:43 2014 laurent ansel
//

#include			"Entities/Guild.hh"

Guild::Guild() :
  Persistent(), Nameable()
{

}

Guild::Guild(std::string const &name) :
  Persistent(), Nameable(name)
{

}

Guild::Guild(Guild const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

Guild::~Guild()
{

}

Guild				&Guild::operator=(Guild const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

bool				Guild::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["GUILD"] = this->getName();
  return (ret);
}

Guild				*Guild::deserialization(Trame const &trame)
{
  Guild			*guild = NULL;

  if (trame.isMember("GUILD"))
    guild = new Guild(trame["GUILD"].asString());
  return (guild);
}

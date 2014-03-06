//
// Faction.cpp for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:31:07 2013 alexis mestag
// Last update Wed Mar  5 15:48:06 2014 laurent ansel
//

#include			"Entities/Faction.hh"
#include			"Effects/PlayerEffect.hh"

Faction::Faction() :
  Persistent(), Nameable()
{

}

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
#ifndef				CLIENT_COMPILATION
      this->setEffectLib(rhs.getEffectLib());
#endif
    }
  return (*this);
}

#ifndef				CLIENT_COMPILATION
EffectLib const			&Faction::getEffectLib() const
{
  return (*_effectLib);
}

void				Faction::setEffectLib(EffectLib const &effectLib)
{
  _effectLib = &effectLib;
}

void				Faction::applyEffect(Player &player) const
{
  PlayerEffect			*effect = static_cast<PlayerEffect *>(_effectLib->getEffect());

  effect->apply(player);
  delete effect;
}
#endif

bool				Faction::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["FACT"] = this->getName();
  return (ret);
}

Faction				*Faction::deserialization(Trame const &trame)
{
  Faction			*faction = NULL;

  if (trame.isMember("FACT"))
    faction = new Faction(trame["FACT"].asString());
  return (faction);
}

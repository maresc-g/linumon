//
// Spells.cpp for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:54:19 2014 alexis mestag
// Last update Fri Jan 31 15:08:45 2014 laurent ansel
//

#include			"Entities/Spells.hh"

Spells::Spells()
{

}

Spells::Spells(Spells const &rhs)
{
  *this = rhs;
}

Spells::~Spells()
{

}

Spells				&Spells::operator=(Spells const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

Spells::containerType const	&Spells::getContainer() const
{
  return (_spells);
}

void				Spells::addSpell(Spell const &spell)
{
  this->_spells.push_back(&spell);
}

bool				Spells::serialization(Trame &trame) const
{
  bool				ret = true;

  for (auto it = this->_spells.begin() ; it != this->_spells.end() && ret; ++it)
    (*it)->serialization(trame(trame["SPELLS"]));
  return (ret);
}

Spells				*Spells::deserialization(Trame const &trame)
{
  Spells			*spells = NULL;
  auto				members = trame.getMemberNames();

  if (trame.isMember("SPELLS"))
    {
      spells = new Spells;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	spells->addSpell(*Spell::deserialization(trame(trame["SPELLS"][*it])));
    }
  return (spells);
}

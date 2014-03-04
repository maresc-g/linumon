//
// Spells.cpp for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:54:19 2014 alexis mestag
// Last update Mon Mar  3 15:55:12 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Spells.hh"

Spells::Spells() :
  ContainerWrapper<container_type>()
{

}

Spells::Spells(Spells const &rhs) :
  ContainerWrapper<container_type>()
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
      this->setContainer(rhs.getContainer());
    }
  return (*this);
}

void				Spells::addSpell(Spell const &spell)
{
  this->getContainer().push_back(&spell);
}

bool				Spells::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;
  unsigned int			nb = 0;

  for (auto it = this->begin() ; it != this->end() && ret; ++it)
    {
      str << nb;
      (*it)->serialization(trame(trame["SPS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Spells				*Spells::deserialization(Trame const &trame)
{
  Spells			*spells = NULL;

  if (trame.isMember("SPS"))
    {
      auto			members = trame["SPS"].getMemberNames();

      spells = new Spells;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	spells->addSpell(*Spell::deserialization(trame(trame["SPS"][*it])));
    }
  return (spells);
}

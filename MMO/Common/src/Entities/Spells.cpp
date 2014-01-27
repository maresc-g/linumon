//
// Spells.cpp for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:54:19 2014 alexis mestag
// Last update Mon Jan 27 13:11:26 2014 laurent ansel
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

bool				Spells::serialization(Trame &) const
{
  bool				ret = true;

  for (auto it = this->_spells.begin() ; it != this->_spells.end() && ret; ++it)
    ;//    ret = (*it)->serialization(trame); /* ARRRRGGGGGGHHHHHHHHHHHHHH !!!!*/
  return (ret);
}

bool				Spells::deserialization(Trame const &)
{
  bool				ret = true;

  for (auto it = this->_spells.begin() ; it != this->_spells.end() && ret; ++it)
    ;//    ret = (*it)->deserialization(trame); /* ARRRRGGGGGGHHHHHHHHHHHHHH !!!!*/
  return (ret);
}

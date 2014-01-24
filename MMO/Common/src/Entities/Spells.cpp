//
// Spells.cpp for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:54:19 2014 alexis mestag
// Last update Fri Jan 24 21:07:58 2014 alexis mestag
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

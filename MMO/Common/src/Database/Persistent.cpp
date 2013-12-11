//
// Persistent.cpp for Persistent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:25:00 2013 alexis mestag
// Last update Thu Dec  5 20:17:08 2013 alexis mestag
//

#include			"Database/Persistent.hh"

Persistent::Persistent() :
  _persistentId(0)
{

}

Persistent::Persistent(Persistent const &rhs)
{
  *this = rhs;
}

Persistent::~Persistent()
{

}

Persistent			&Persistent::operator=(Persistent const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

unsigned long			Persistent::getPersistentId() const
{
  return (_persistentId);
}

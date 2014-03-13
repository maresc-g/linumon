//
// Persistent.cpp for Persistent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:25:00 2013 alexis mestag
// Last update Thu Mar 13 14:36:34 2014 alexis mestag
//

#include			"Database/Persistent.hh"

Persistent::Persistent() :
  _persistentId(0)
{

}

Persistent::Persistent(Persistent const &rhs) :
  _persistentId(0)
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

bool				Persistent::isPersistent() const
{
  return (this->getPersistentId() ? true : false);
}

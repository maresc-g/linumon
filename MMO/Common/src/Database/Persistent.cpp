//
// Persistent.cpp for Persistent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:25:00 2013 alexis mestag
// Last update Tue Dec  3 10:56:50 2013 alexis mestag
//

#include			"Database/Persistent.hh"

Persistent::Persistent()
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

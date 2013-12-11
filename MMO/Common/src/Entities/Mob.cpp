//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Thu Dec  5 22:03:53 2013 alexis mestag
//

#include			"Entities/Mob.hh"

Mob::Mob() :
  Persistent(), ACharacter("", eCharacter::MOB)
{

}

Mob::Mob(Mob const &rhs) :
  Persistent(rhs), ACharacter(rhs)
{
  *this = rhs;
}

Mob::~Mob()
{

}

Mob				&Mob::operator=(Mob const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
    }
  return (*this);
}

Type const			&Mob::getType() const
{
  return (*_type);
}

void				Mob::setType(Type const &type)
{
  _type = &type;
}

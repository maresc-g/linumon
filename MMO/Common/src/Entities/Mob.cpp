//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Mon Jan 27 13:08:54 2014 laurent ansel
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
      this->setModel(rhs.getModel());
    }
  return (*this);
}

MobModel const			&Mob::getModel() const
{
  return (*_model);
}

void				Mob::setModel(MobModel const &model)
{
  _model = &model;
}

bool				Mob::serialization(Trame &) const
{
  bool				ret = false;
  return (ret);
}

bool				Mob::deserialization(Trame const &)
{
  bool				ret = false;
  return (ret);
}

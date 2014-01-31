//
// Spell.cpp for Spell in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 22:54:34 2013 alexis mestag
// Last update Fri Jan 31 15:14:47 2014 laurent ansel
//

#include			"Entities/Spell.hh"

Spell::Spell() :
  Persistent(), Nameable(""), _type(NULL), _power(0)
{

}

Spell::Spell(Spell const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

Spell::~Spell()
{

}

Spell				&Spell::operator=(Spell const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
      this->setPower(rhs.getPower());
      this->setUseLimit(rhs.getUseLimit());
    }
  return (*this);
}

Type const			&Spell::getType() const
{
  return (*_type);
}

void				Spell::setType(Type const &type)
{
  _type = &type;
}

int				Spell::getPower() const
{
  return (_power);
}

void				Spell::setPower(int const power)
{
  _power = power;
}

int				Spell::getUseLimit() const
{
  return (_useLimit);
}

void				Spell::setUseLimit(int const useLimit)
{
  _useLimit = useLimit;
}

bool				Spell::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[this->getName()]["NAME"] = this->getName();
  this->_type->serialization(trame(trame[this->getName()]));
  trame[this->getName()]["POWER"] = this->_power;
  trame[this->getName()]["USELIMIT"] = this->_useLimit;
  return (ret);
}

Spell				*Spell::deserialization(Trame const &trame)
{
  Spell				*spell = new Spell;

  spell->setType(*Type::deserialization(trame));
  spell->setName(trame["NAME"].asString());
  spell->setPower(trame["POWER"].asInt());
  spell->setUseLimit(trame["USELIMIT"].asInt());
  return (spell);
}

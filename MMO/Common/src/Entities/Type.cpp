//
// Type.cpp for Type in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 21:14:39 2013 alexis mestag
// Last update Thu Feb 27 17:53:15 2014 alexis mestag
//

#include			"Entities/Type.hh"

Type::Type() :
  Persistent(), Nameable()
{

}

Type::Type(std::string const &name) :
  Persistent(), Nameable(name)
{

}

Type::Type(Type const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

Type::~Type()
{

}

Type				&Type::operator=(Type const &rhs)
{
  if (this != &rhs)
    {
      this->setRelations(rhs.getRelations());
    }
  return (*this);
}

bool				Type::operator==(Type const &rhs) const
{
  return (this->getName() == rhs.getName());
}

bool				Type::operator!=(Type const &rhs) const
{
  return (!(*this == rhs));
}

TypeRelations const		&Type::getRelations() const
{
  return (_relations);
}

void				Type::setRelations(TypeRelations const &relations)
{
  _relations = relations;
}

TypeRelations::Link::coeff_type	Type::getCoeffAgainst(Type const &type) const
{
  return (this->getRelations().getCoeffOf(type));
}

bool				Type::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["TYPE"] = this->getName();
  return (ret);
}

Type				*Type::deserialization(Trame const &trame)
{
  Type				*type = NULL;

  if (trame.isMember("TYPE"))
    type = new Type(trame["TYPE"].asString());
  return (type);
}

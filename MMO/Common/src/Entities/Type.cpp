//
// Type.cpp for Type in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 21:14:39 2013 alexis mestag
// Last update Tue Dec 10 14:31:58 2013 alexis mestag
//

#include			"Entities/Type.hh"

Type::Type() :
  Persistent(), Nameable(), _relations(new TypeRelations)
{

}

Type::Type(std::string const &name) :
  Persistent(), Nameable(name), _relations(new TypeRelations)
{

}

Type::Type(Type const &rhs) :
  Persistent(rhs), Nameable(rhs), _relations(new TypeRelations)
{
  *this = rhs;
}

Type::~Type()
{
  delete _relations;
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
  return (*_relations);
}

void				Type::setRelations(TypeRelations const &relations)
{
  *_relations = relations;
}

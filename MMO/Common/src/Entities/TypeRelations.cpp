//
// TypeRelations.cpp for TypeRelations in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  9 18:28:39 2013 alexis mestag
// Last update Tue Dec 10 13:19:33 2013 alexis mestag
//

#include			"Entities/Type.hh"

TypeRelations::TypeRelations() :
  _relations(new Relations)
{

}

TypeRelations::TypeRelations(TypeRelations const &rhs) :
  TypeRelations()
{
  *this = rhs;
}

TypeRelations::~TypeRelations()
{
  delete _relations;
}

TypeRelations			&TypeRelations::operator=(TypeRelations const &rhs)
{
  if (this != &rhs)
    {
      this->setRelations(rhs.getRelations());
    }
  return (*this);
}

TypeRelations::Relations const	&TypeRelations::getRelations() const
{
  return (*_relations);
}

void				TypeRelations::setRelations(Relations const &relations)
{
  for (auto it = relations.cbegin() ; it != relations.cend() ; ++it)
    {
      _relations->push_back(*it);
    }
}

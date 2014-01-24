//
// TypeRelations.cpp for TypeRelations in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  9 18:28:39 2013 alexis mestag
// Last update Fri Jan 24 15:22:45 2014 alexis mestag
//

#include			"Entities/Type.hh"

TypeRelations::TypeRelations()
{

}

TypeRelations::TypeRelations(TypeRelations const &rhs)
{
  *this = rhs;
}

TypeRelations::~TypeRelations()
{

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
  return (_relations);
}

void				TypeRelations::setRelations(Relations const &relations)
{
  for (auto it = relations.cbegin() ; it != relations.cend() ; ++it)
    {
      _relations.push_back(*it);
    }
}

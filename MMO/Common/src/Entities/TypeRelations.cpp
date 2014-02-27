//
// TypeRelations.cpp for TypeRelations in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  9 18:28:39 2013 alexis mestag
// Last update Thu Feb 27 17:55:26 2014 alexis mestag
//

#include			<algorithm>
#include			<functional>
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

TypeRelations::Link::coeff_type	TypeRelations::getCoeffOf(Type const &type) const
{
  std::function<bool(Link)>	typeSeeker = [&](Link link) -> bool {
    return (*link.type == type);
  };
  auto				it = std::find_if(this->getRelations().begin(),
						  this->getRelations().end(),
						  typeSeeker);
  Link::coeff_type		ret = 1;

  if (it != this->getRelations().end())
    ret = it->coeff;
  return (ret);
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

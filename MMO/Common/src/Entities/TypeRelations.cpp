//
// TypeRelations.cpp for TypeRelations in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  9 18:28:39 2013 alexis mestag
// Last update Mon Mar  3 16:53:37 2014 alexis mestag
//

#include			<algorithm>
#include			<functional>
#include			"Entities/Type.hh"

TypeRelations::TypeRelations() :
  ContainerWrapper<container_type>()
{

}

TypeRelations::TypeRelations(TypeRelations const &rhs) :
  ContainerWrapper<container_type>()
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

Link::coeff_type		TypeRelations::getCoeffOf(Type const &type) const
{
  std::function<bool(Link)>	typeSeeker = [&](Link link) -> bool {
    return (*link.type == type);
  };
  auto				it = std::find_if(this->begin(), this->end(), typeSeeker);
  Link::coeff_type		ret = 1;

  if (it != this->end())
    ret = it->coeff;
  return (ret);
}

TypeRelations::container_type const	&TypeRelations::getRelations() const
{
  return (this->getContainer());
}

void				TypeRelations::setRelations(container_type const &relations)
{
  this->setContainer(relations);
}

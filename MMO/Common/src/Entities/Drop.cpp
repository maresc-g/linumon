//
// Drop.cpp for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:10 2014 antoine maitre
// Last update Sun Mar 16 18:20:43 2014 alexis mestag
//

#include			"Entities/Drop.hh"

Drop::Drop() :
  ContainerWrapper<container_type>()
{
  
}

Drop::Drop(Drop const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Drop::~Drop()
{
  
}

Drop				&Drop::operator=(Drop const &rhs)
{
  if (this != &rhs)
    {
      this->setContainer(rhs.getContainer());
    }
  return (*this);
}

void				Drop::clear()
{
  this->getContainer().clear();
}

void				Drop::addItem(AItem *item, unsigned int const nb)
{
  this->getContainer().push_back(Stack<AItem>(0, item, nb));
}

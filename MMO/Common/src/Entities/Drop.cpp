//
// Drop.cpp for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:10 2014 antoine maitre
// Last update Mon Mar 24 10:25:57 2014 alexis mestag
//

#include			<algorithm>
#include			<functional>
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

Drop				&Drop::operator+=(Drop const &rhs)
{
  this->add(rhs);
  return (*this);
}

void				Drop::clear()
{
  this->getContainer().clear();
}

Stack<AItem>			*Drop::getStack(AItem *item)
{
  std::function<bool(Stack<AItem> &s)>	stackSeeker = [&](Stack<AItem> &s) {
    return (item == s.getItem());
  };
  auto					it = std::find_if(this->begin(), this->end(), stackSeeker);

  return (it != this->end() ? &*it : NULL);
}

void				Drop::addItem(AItem *item, unsigned int const nb)
{
  Stack<AItem>			*stack = this->getStack(item);

  if (stack) {
    stack->setNb(stack->getNb() + nb);
  }
  else
    this->getContainer().push_back(Stack<AItem>(0, item, nb));
}

Drop				&Drop::add(Drop const &rhs)
{
  std::for_each(rhs.begin(), rhs.end(), [&](Stack<AItem> const &s) -> void {
      this->addItem(s.getItem(), s.getNb());
    });
  return (*this);
}

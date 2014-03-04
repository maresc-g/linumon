//
// Talents.cpp for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:06:53 2014 alexis mestag
// Last update Tue Mar  4 00:14:19 2014 alexis mestag
//

#include				"Stats/Talents.hh"

Talents::Talents() :
  ContainerWrapper<container_type>()
{

}

Talents::Talents(Talents const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Talents::~Talents()
{

}

Talents					&Talents::operator=(Talents const &rhs)
{
  if (this != &rhs)
    {
      this->setTalents(rhs.getTalents());
    }
  return (*this);
}

Talents::container_type const		&Talents::getTalents() const
{
  return (this->getContainer());
}

void					Talents::setTalents(container_type const &talents)
{
  this->setContainer(talents);
}

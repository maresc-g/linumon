//
// Id.cpp for Id in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 10:34:09 2013 alexis mestag
// Last update Thu Feb  6 15:32:49 2014 laurent ansel
//

#include			"Utility/Id.hh"

Id::Id() :
  _id(0)
{
  static unsigned int		id = 0;

  _id = id++;
}

Id::Id(Id const &rhs)
{
  *this = rhs;
}

Id::~Id()
{

}

Id				&Id::operator=(Id const &rhs)
{
  if (this != &rhs)
    {
      this->setId(rhs.getId());
    }
  return (*this);
}

unsigned long			Id::getId() const
{
  return (_id);
}

void				Id::setId(unsigned long const id)
{
  _id = id;
}

//
// Id.cpp for Id in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 10:34:09 2013 alexis mestag
// Last update Tue Dec  3 10:36:16 2013 alexis mestag
//

#include			"Utility/Id.hh"

Id::Id() :
  _id(0)
{

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

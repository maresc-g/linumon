//
// Equipment.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:28:56 2014 laurent ansel
// Last update Thu Feb  6 16:38:15 2014 laurent ansel
//

#include			"Entities/Equipment.hh"

Equipment::Equipment():
  _stuffs(new std::list<Stuff *>)
{
}

Equipment::~Equipment()
{
}

Equipment::Equipment(Equipment const &rhs)
{
  *this = rhs;
}

Equipment			&Equipment::operator=(Equipment const &rhs)
{
  if (this != &rhs)
    {
      // I'm not going to copy the mobs'list :)
    }
  return (*this);
}

std::list<Stuff *> const	&Equipment::getStuffs() const
{
  return (*this->_stuffs);
}

void				Equipment::setStuffs(std::list<Stuff *> const &list)
{
  *this->_stuffs = list;
}

bool				Equipment::serialization(Trame &) const
{
  return (false);
}

Equipment			*Equipment::deserialization(Trame const &)
{
  Equipment			*equipment = NULL;

  return (equipment);
}


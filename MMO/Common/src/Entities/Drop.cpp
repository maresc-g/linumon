//
// Drop.cpp for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:10 2014 antoine maitre
// Last update Sat Mar 15 01:35:28 2014 alexis mestag
//

#include			"Entities/Drop.hh"

Drop::Drop() :
  Inventory("Toto")
{
  
}

Drop::Drop(Drop const &rhs) :
  Inventory("Toto")
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

    }
  return (*this);
}

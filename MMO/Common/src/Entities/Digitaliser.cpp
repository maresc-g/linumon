//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Fri Jan 24 14:44:52 2014 alexis mestag
//

#include			"Entities/Digitaliser.hh"

Digitaliser::Digitaliser()
{

}

Digitaliser::Digitaliser(Digitaliser const &rhs)
{
  *this = rhs;
}

Digitaliser::~Digitaliser()
{

}

Digitaliser			&Digitaliser::operator=(Digitaliser const &rhs)
{
  if (this != &rhs)
    {
      // I'm not going to copy the mobs'list :)
    }
  return (*this);
}

Digitaliser::Mobs const		&Digitaliser::getMobs() const
{
  return (_mobs);
}

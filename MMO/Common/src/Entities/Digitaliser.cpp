//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Tue Dec 10 15:22:10 2013 alexis mestag
//

#include			"Entities/Digitaliser.hh"

Digitaliser::Digitaliser() :
  _mobs(new Mobs)
{

}

Digitaliser::Digitaliser(Digitaliser const &rhs)
{
  *this = rhs;
}

Digitaliser::~Digitaliser()
{
  delete _mobs;
}

Digitaliser			&Digitaliser::operator=(Digitaliser const &rhs)
{
  if (this != &rhs)
    {
      // I'm not going to copy the mobs'list :)
    }
  return (*this);
}

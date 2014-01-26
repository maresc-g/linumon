//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Sun Jan 26 14:48:04 2014 laurent ansel
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

bool				Digitaliser::serialization(Trame &trame)
{
  bool				ret = true;

  for (auto it = this->_mobs.begin() ; it != this->_mobs.end() && ret; ++it)
    ret = (*it)->serialization(trame);
  return (ret);
}

bool				Digitaliser::deserialization(Trame const &trame)
{
  bool				ret = true;

  for (auto it = this->_mobs.begin() ; it != this->_mobs.end() && ret; ++it)
    ret = (*it)->deserialization(trame);
  return (ret);
}

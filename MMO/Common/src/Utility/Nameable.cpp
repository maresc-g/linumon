//
// Nameable.cpp for Nameable in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:49:14 2013 alexis mestag
// Last update Tue Dec  3 10:57:20 2013 alexis mestag
//

#include			"Utility/Nameable.hh"

Nameable::Nameable(std::string const &name) :
  _name(name)
{

}

Nameable::Nameable(Nameable const &rhs)
{
  *this = rhs;
}

Nameable::~Nameable()
{

}

Nameable			&Nameable::operator=(Nameable const &rhs)
{
  if (this != &rhs)
    {
      this->setName(rhs.getName());
    }
  return (*this);
}

std::string const		&Nameable::getName() const
{
  return (_name);
}

void				Nameable::setName(std::string const &name)
{
  _name = name;
}

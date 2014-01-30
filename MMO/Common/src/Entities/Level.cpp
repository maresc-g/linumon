//
// Level.cpp for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 14:08:00 2014 alexis mestag
// Last update Wed Jan 29 14:35:35 2014 alexis mestag
//

#include			"Entities/Level.hh"

Level::Level() : _lvl(0), _exp(0)
{

}

Level::Level(Level const &rhs)
{
  *this = rhs;
}

Level::~Level()
{

}

Level				&Level::operator=(Level const &rhs)
{
  if (this != &rhs)
    {
      this->setLevel(rhs.getLevel());
      this->setExp(rhs.getExp());
    }
  return (*this);
}

int				Level::getLevel() const
{
  return (_lvl);
}

void				Level::setLevel(int const level)
{
  _lvl = level;
}

int				Level::getExp() const
{
  return (_exp);
}

void				Level::setExp(int const exp)
{
  _exp = exp;
}

void				Level::levelUp()
{
  this->setLevel(this->getLevel() + 1);
  this->setExp(this->getExp() * 1.25);
}

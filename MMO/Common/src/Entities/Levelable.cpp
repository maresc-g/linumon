//
// Level.cpp for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 14:08:00 2014 alexis mestag
// Last update Mon Mar 24 16:22:45 2014 alexis mestag
//

#include			"Entities/Levelable.hh"

Levelable::Levelable() :
  _currentExp(0), _level(0), _exp(0), _oldExp(0)
{

}

Levelable::Levelable(Levelable const &rhs)
{
  *this = rhs;
}

Levelable::Levelable(type const currentExp, type const level, type const exp) :
  _currentExp(currentExp), _level(level), _exp(exp), _oldExp(0)
{

}

Levelable::~Levelable()
{

}

Levelable				&Levelable::operator=(Levelable const &rhs)
{
  if (this != &rhs)
    {
      this->setCurrentExp(rhs.getCurrentExp(), false);
      this->setLevel(rhs.getLevel());
      this->setExp(rhs.getExp());
      this->setOldExp(rhs.getOldExp());
    }
  return (*this);
}

Levelable::type			Levelable::getCurrentExp() const
{
  return (_currentExp);
}

unsigned int			Levelable::setCurrentExp(type const currentExp, bool const check)
{
  unsigned int			ret = 0;

  _currentExp = currentExp;
  if (check)
    ret = this->checkLevelUp();
  return (ret);
}

unsigned int			Levelable::incCurrentExp(type const inc, bool const check)
{
  unsigned int			ret = 0;

  _currentExp += inc;
  if (check)
    ret = this->checkLevelUp();
  return (ret);
}

Levelable::type			Levelable::getLevel() const
{
  return (_level);
}

void				Levelable::setLevel(type const level)
{
  _level = level;
}

Levelable::type			Levelable::getExp() const
{
  return (_exp);
}

void				Levelable::setExp(type const exp)
{
  _exp = exp;
}

Levelable::type			Levelable::getOldExp() const
{
  return (_oldExp);
}

void				Levelable::setOldExp(type const oldExp)
{
  _oldExp = oldExp;
}

unsigned int			Levelable::checkLevelUp()
{
  unsigned int			ret = 0;

  while (_currentExp >= this->getExp()) {
    this->levelUp();
    ret++;
  }
  return (ret);
}

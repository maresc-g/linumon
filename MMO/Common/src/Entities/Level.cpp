//
// Level.cpp for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 14:08:00 2014 alexis mestag
// Last update Fri Feb 28 13:39:41 2014 laurent ansel
//

#include			"Entities/Level.hh"

Level::Level() : _lvl(1), _exp(0)
{

}

Level::Level(Level const &rhs)
{
  *this = rhs;
}

Level::Level(unsigned int const lvl, unsigned int const exp) :
  _lvl(lvl), _exp(exp)
{

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

unsigned int			Level::getLevel() const
{
  return (_lvl);
}

void				Level::setLevel(unsigned int const level)
{
  _lvl = level;
}

unsigned int			Level::getExp() const
{
  return (_exp);
}

void				Level::setExp(unsigned int const exp)
{
  _exp = exp;
}

void				Level::levelUp()
{
  this->setLevel(this->getLevel() + 1);
  this->setExp(this->getExp() * 1.25);
}

bool				Level::serialization(Trame &trame) const
{
  trame["LVL"]["LVL"] = this->getLevel();
  trame["LVL"]["EXP"] = this->getExp();
  return (true);
}

Level				*Level::deserialization(Trame const &trame)
{
  Level				*level = NULL;

  if (trame.isMember("LVL"))
    {
      level = new Level;
      level->setLevel(trame["LVL"]["LVL"].asUInt());
      level->setExp(trame["LVL"]["EXP"].asUInt());
    }
  return (level);
}

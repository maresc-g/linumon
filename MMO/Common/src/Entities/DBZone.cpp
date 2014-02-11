//
// DBZone.cpp for DBZone in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 10 14:23:57 2014 alexis mestag
// Last update Mon Feb 10 16:27:15 2014 alexis mestag
//

#include			"Entities/DBZone.hh"

DBZone::DBZone() :
  Persistent(), Nameable(), _averageLevel(0)
{

}

DBZone::DBZone(std::string const &name, unsigned int const averageLevel) :
  Persistent(), Nameable(name), _averageLevel(averageLevel)
{

}

DBZone::DBZone(DBZone const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

DBZone::~DBZone()
{

}

DBZone				&DBZone::operator=(DBZone const &rhs)
{
  if (this != &rhs)
    {
      this->setMobModels(rhs.getMobModels());
      this->setAverageLevel(rhs.getAverageLevel());
    }
  return (*this);
}

std::list<MobModel *> const	&DBZone::getMobModels() const
{
  return (_mobModels);
}

void				DBZone::setMobModels(std::list<MobModel *> const &mobModels)
{
  _mobModels = mobModels;
}

unsigned int			DBZone::getAverageLevel() const
{
  return (_averageLevel);
}

void				DBZone::setAverageLevel(unsigned const averageLevel)
{
  _averageLevel = averageLevel;
}

Mob				*DBZone::getRandomMob() const
{
  Mob				*ret = NULL;

  if (this->getMobModels().size()) {
    ret = new Mob(**this->getMobModels().begin(), this->getAverageLevel());
  }
  return (ret);
}

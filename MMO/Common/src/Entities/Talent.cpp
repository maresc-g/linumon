//
// Talent.cpp for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 15:12:32 2014 alexis mestag
// Last update Wed Jan 29 15:19:29 2014 alexis mestag
//

#include			"Entities/Talent.hh"

Talent::Talent() :
  Persistent(), Id(), Nameable(), _maxPoints(0), _currentPoints(0), _rank(0)
{

}

Talent::Talent(Talent const &rhs) :
  Persistent(rhs), Id(rhs), Nameable(rhs)
{
  *this = rhs;
}

Talent::~Talent()
{

}

Talent				&Talent::operator=(Talent const &rhs)
{
  if (this != &rhs)
    {
      this->setMaxPoints(rhs.getMaxPoints());
      this->setCurrentPoints(rhs.getCurrentPoints());
      this->setRank(rhs.getRank());
    }
  return (*this);
}

int				Talent::getMaxPoints() const
{
  return (_maxPoints);
}

void				Talent::setMaxPoints(int const maxPoints)
{
  _maxPoints = maxPoints;
}

int				Talent::getCurrentPoints() const
{
  return (_currentPoints);
}

void				Talent::setCurrentPoints(int const currentPoints)
{
  _currentPoints = currentPoints;
}

int				Talent::getRank() const
{
  return (_rank);
}

void				Talent::setRank(int const rank)
{
  _rank = rank;
}

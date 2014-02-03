//
// Talent.cpp for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 14:51:25 2014 alexis mestag
// Last update Fri Jan 31 15:28:06 2014 alexis mestag
//

#include			"Stats/Talent.hh"

Talent::Talent() :
  Persistent(), _model(NULL), _currentPoints(0)
{

}

Talent::Talent(Talent const &rhs) :
  Persistent()
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
      this->setModel(rhs.getModel());
      this->setCurrentPoints(rhs.getCurrentPoints());
    }
  return (*this);
}

TalentModel const		&Talent::getModel() const
{
  return (*_model);
}

void				Talent::setModel(TalentModel const &model)
{
  _model = &model;
}

int				Talent::getCurrentPoints() const
{
  return (_currentPoints);
}

void				Talent::setCurrentPoints(int const currentPoints)
{
  _currentPoints = currentPoints;
}

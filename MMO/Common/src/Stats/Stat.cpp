//
// Stat.cpp for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:08:36 2013 alexis mestag
// Last update Thu Dec  5 20:01:16 2013 alexis mestag
//

#include			"Stats/Stat.hh"

Stat::Stat() :
  Persistent(), _statType(eStat::NONE), _value(0)
{

}

Stat::Stat(Stat::eStat const statType, int const value) :
  Persistent(), _statType(statType), _value(value)
{

}

Stat::Stat(Stat const &rhs) :
  Persistent(rhs)
{
  *this = rhs;
}

Stat::~Stat()
{

}

Stat				&Stat::operator=(Stat const &rhs)
{
  if (this != &rhs)
    {
      this->setStatType(rhs.getStatType());
      this->setValue(rhs.getValue());
    }
  return (*this);
}

int				Stat::getValue() const
{
  return (_value);
}

void				Stat::setValue(int const value)
{
  _value = value;
}

Stat::eStat			Stat::getStatType() const
{
  return (_statType);
}

void				Stat::setStatType(Stat::eStat const statType)
{
  _statType = statType;
}
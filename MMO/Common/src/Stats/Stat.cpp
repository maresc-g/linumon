//
// Stat.cpp for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:08:36 2013 alexis mestag
// Last update Fri Mar 21 19:07:16 2014 alexis mestag
//

#include			<sstream>
#include			"Stats/Stat.hh"

Stat::Stat() :
  _key(NULL), _rawValue(0), _bonus(0)
{

}

Stat::Stat(StatKey const &key, value_type const value, bonus_type const bonus) :
  _key(&key), _rawValue(value), _bonus(bonus)
{

}

Stat::Stat(Stat const &rhs)
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
      this->setKey(rhs.getKey());
      this->setRawValue(rhs.getRawValue());
      this->setBonus(rhs.getBonus());
    }
  return (*this);
}

bool				Stat::operator==(Stat const &rhs) const
{
  return (this->getKey() == rhs.getKey());
}

bool				Stat::operator!=(Stat const &rhs) const
{
  return (!(*this == rhs));
}

Stat				Stat::operator+(Stat const &rhs) const
{
  Stat				ret(*this);

  ret += rhs;
  return (ret);
}

Stat				&Stat::operator+=(Stat const &rhs)
{
  this->add(rhs);
  return (*this);
}

Stat				Stat::operator-(Stat const &rhs) const
{
  Stat				ret(*this);

  ret -= rhs;
  return (ret);
}

Stat				&Stat::operator-=(Stat const &rhs)
{
  this->sub(rhs);
  return (*this);
}

void				Stat::add(Stat const &rhs)
{
  if (this->getKey() == rhs.getKey()) {
    this->setRawValue(this->getRawValue() + rhs.getRawValue());
    this->setBonus(this->getBonus() + rhs.getBonus());
  }
}

void				Stat::sub(Stat const &rhs)
{
  if (this->getKey() == rhs.getKey()) {
    this->setRawValue(rhs.getRawValue() >= this->getRawValue() ? 0 :
		      this->getRawValue() - rhs.getRawValue());
    this->setBonus(this->getBonus() - rhs.getBonus());
  }
}

StatKey const			&Stat::getKey() const
{
  return (*_key);
}

void				Stat::setKey(StatKey const &key)
{
  _key = &key;
}

Stat::value_type		Stat::getRawValue() const
{
  return (_rawValue);
}

void				Stat::setRawValue(value_type const value)
{
  _rawValue = value;
}

Stat::bonus_type		Stat::getBonus() const
{
  return (_bonus);
}

void				Stat::setBonus(bonus_type const bonus)
{
  _bonus = bonus;
}

Stat::value_type		Stat::getValue() const
{
  return (_rawValue + _rawValue * this->getBonus() / 100.0);
}

bool				Stat::isShortLived() const
{
  return (_key->isShortLived());
}

bool		 		Stat::serialization(Trame &trame) const
{
  bool				ret = true;

  // trame["KEY"] = this->getKey().getName();
  trame[this->getKey().getName()]["VALUE"] = this->getRawValue();
  trame[this->getKey().getName()]["BONUS"] = this->getBonus();
  return (ret);
}

Stat				*Stat::deserialization(Trame const &trame)
{
  Stat				*stat = NULL;

  //  stat = new Stat(*new StatKey(trame["KEY"].asString()), trame["VALUE"].asInt());
  stat = new Stat();
  stat->setRawValue(trame["VALUE"].asUInt());
  stat->setBonus(trame["BONUS"].asInt());
  return (stat);
}

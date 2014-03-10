//
// Stat.cpp for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:08:36 2013 alexis mestag
// Last update Mon Mar 10 01:14:10 2014 alexis mestag
//

#include			<sstream>
#include			"Stats/Stat.hh"
#ifndef			CLIENT_COMPILATION
# include		"Stats/Stat-odb.hxx"
# include		"Database/Database.hpp"
#endif

Stat::Stat() :
  Persistent(), _key(NULL), _value(0)
{

}

Stat::Stat(StatKey const &key, value_type const value) :
  Persistent(), _key(&key), _value(value)
{

}

Stat::Stat(Stat const &rhs) :
  Persistent(rhs)
{
  *this = rhs;
}

Stat::~Stat()
{
#ifndef			CLIENT_COMPILATION
  Repository<Stat>	*rs = &Database::getRepository<Stat>();
  rs->removeFromCache(*this);
#endif
}

Stat				&Stat::operator=(Stat const &rhs)
{
  if (this != &rhs)
    {
      this->setKey(rhs.getKey());
      this->setValue(rhs.getValue());
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
  if (this->getKey() == rhs.getKey())
    this->setValue(this->getValue() + rhs.getValue());
}

void				Stat::sub(Stat const &rhs)
{
  if (this->getKey() == rhs.getKey())
    this->setValue(rhs.getValue() >= this->getValue() ? 0 : this->getValue() - rhs.getValue());
}

StatKey const			&Stat::getKey() const
{
  return (*_key);
}

void				Stat::setKey(StatKey const &key)
{
  _key = &key;
}

Stat::value_type		Stat::getValue() const
{
  return (_value);
}

void				Stat::setValue(value_type const value)
{
  _value = value;
}

bool				Stat::isShortLived() const
{
  return (_key->isShortLived());
}

bool		 		Stat::serialization(Trame &trame) const
{
  bool				ret = true;

  // trame["KEY"] = this->getKey().getName();
  trame[this->getKey().getName()] = this->getValue();
  return (ret);
}

Stat				*Stat::deserialization(Trame const &trame)
{
  Stat				*stat = NULL;

  //  stat = new Stat(*new StatKey(trame["KEY"].asString()), trame["VALUE"].asInt());
  stat = new Stat();
  stat->setValue(trame.asUInt());
  return (stat);
}

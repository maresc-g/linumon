//
// Stat.cpp for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:08:36 2013 alexis mestag
// Last update Thu Feb 20 12:46:35 2014 alexis mestag
//

#include			<sstream>
#include			"Stats/Stat.hh"

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

bool		 		Stat::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;

  str << "STAT" << this->getKey().getName();
  trame[str.str()]["KEY"] = this->getKey().getName();
  trame[str.str()]["VALUE"] = this->getValue();
  return (ret);
}

Stat				*Stat::deserialization(Trame const &trame)
{
  Stat				*stat = NULL;

  stat = new Stat(*new StatKey(trame["KEY"].asString()), trame["VALUE"].asInt());
  return (stat);
}

//
// StatKey.cpp for StatKey in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 19 15:02:05 2014 alexis mestag
// Last update Thu Feb 20 13:01:01 2014 alexis mestag
//

#include				"Stats/StatKey.hh"

StatKey::StatKey() :
  Persistent(), Nameable()
{

}

StatKey::StatKey(std::string const &key) :
  Persistent(), Nameable(key)
{

}

StatKey::StatKey(StatKey const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

StatKey::~StatKey()
{

}

StatKey					&StatKey::operator=(StatKey const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

bool					StatKey::operator==(StatKey const &rhs) const
{
  bool					ret = true;

  if (this != &rhs)
    ret = this->getName() == rhs.getName();
  return (ret);
}

bool					StatKey::operator!=(StatKey const &rhs) const
{
  return (!(*this == rhs));
}

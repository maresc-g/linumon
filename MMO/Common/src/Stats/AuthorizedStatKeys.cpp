//
// AuthorizedStatKeys.cpp for AuthorizedStatKeys in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 20 13:36:32 2014 alexis mestag
// Last update Thu Feb 20 22:25:45 2014 alexis mestag
//

#include				<algorithm>
#include				"Stats/AuthorizedStatKeys.hh"

AuthorizedStatKeys::AuthorizedStatKeys() :
  Persistent(), Nameable()
{

}

AuthorizedStatKeys::AuthorizedStatKeys(AuthorizedStatKeys const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

AuthorizedStatKeys::~AuthorizedStatKeys()
{

}

AuthorizedStatKeys			&AuthorizedStatKeys::operator=(AuthorizedStatKeys const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

bool					AuthorizedStatKeys::isAuthorized(StatKey const &key) const
{
  auto					it = std::find(_keys.cbegin(), _keys.cend(), &key);

  return (it != _keys.cend() ? true : false);
}

bool					AuthorizedStatKeys::addKey(StatKey const &key)
{
  bool					ret = false;

  if (!this->isAuthorized(key)) {
    _keys.push_back(&key);
    ret = true;
  }
  return (ret);
}

bool					AuthorizedStatKeys::removeKey(StatKey const &key)
{
  bool					ret = false;

  if (this->isAuthorized(key)) {
    _keys.remove(&key);
    ret = true;
  }
  return (ret);
}

AuthorizedStatKeys::container_type const	&AuthorizedStatKeys::getKeys() const
{
  return (_keys);
}

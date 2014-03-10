//
// AuthorizedStatKeys.cpp for AuthorizedStatKeys in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 20 13:36:32 2014 alexis mestag
// Last update Thu Mar  6 15:19:54 2014 laurent ansel
//

#include				<algorithm>
#include				"Stats/AuthorizedStatKeys.hh"

AuthorizedStatKeys::AuthorizedStatKeys() :
  Persistent(), Nameable(), ContainerWrapper<container_type>()
{

}

AuthorizedStatKeys::AuthorizedStatKeys(AuthorizedStatKeys const &rhs) :
  Persistent(rhs), Nameable(rhs), ContainerWrapper<container_type>()
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
      this->setKeys(rhs.getKeys());
    }
  return (*this);
}

bool					AuthorizedStatKeys::isAuthorized(StatKey const &key) const
{
  std::function<bool(StatKey const *)>	statKeySeeker = [&](StatKey const *sk) -> bool {
    return (*sk == key);
  };
  auto					it = std::find_if(this->cbegin(), this->cend(), statKeySeeker);

  return (it != this->cend() ? true : false);
}

bool					AuthorizedStatKeys::addKey(StatKey const &key)
{
  bool					ret = false;

  if (!this->isAuthorized(key)) {
    this->getContainer().push_back(&key);
    ret = true;
  }
  return (ret);
}

bool					AuthorizedStatKeys::removeKey(StatKey const &key)
{
  bool					ret = false;

  if (this->isAuthorized(key)) {
    this->getContainer().remove(&key);
    ret = true;
  }
  return (ret);
}

AuthorizedStatKeys::container_type const	&AuthorizedStatKeys::getKeys() const
{
  return (this->getContainer());
}

void						AuthorizedStatKeys::setKeys(AuthorizedStatKeys::container_type const &k)
{
  this->setContainer(k);
}

StatKey const					*AuthorizedStatKeys::getKey(std::string const &key) const
{
  std::function<bool(StatKey const *)>		statKeySeeker = [&](StatKey const *sk) {
    return (sk->getName() == key);
  };
  StatKey const					*ret = NULL;
  auto						it = std::find_if(this->cbegin(), this->cend(),
								  statKeySeeker);

  if (it != this->cend())
    ret = *it;
  return (ret);
}

bool						AuthorizedStatKeys::serialization(Trame &trame) const
{
  bool						ret = true;

  for (auto it = this->begin() ; it != this->end() ; ++it)
    trame[(*it)->getName()] = (*it)->isShortLived();;
  return (ret);
}

AuthorizedStatKeys				*AuthorizedStatKeys::deserialization(Trame const &trame)
{
  AuthorizedStatKeys				*authorizedStatKeys = new AuthorizedStatKeys;
  auto						members = trame.getMemberNames();

  for (auto it = members.begin() ; it != members.end() ; ++it)
    authorizedStatKeys->addKey(*new StatKey(*it, trame[*it].asBool()));
  return (authorizedStatKeys);
}

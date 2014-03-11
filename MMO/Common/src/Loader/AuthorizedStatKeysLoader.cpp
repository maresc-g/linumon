//
// AuthorizedStatKeysLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 13:54:26 2014 laurent ansel
// Last update Mon Mar 10 19:11:19 2014 alexis mestag
//

#ifndef CLIENT_COMPILATION
# include			"Stats/AuthorizedStatKeys-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/AuthorizedStatKeysLoader.hh"

/*
**
**	AuthorizedStatKeys
**
*/

AuthorizedStatKeysList::AuthorizedStatKeysList() :
  _authorizedStatKeysList(new std::list<AuthorizedStatKeys *>)
{
#ifndef CLIENT_COMPILATION
  Repository<AuthorizedStatKeys>		*mm = &Database::getRepository<AuthorizedStatKeys>();

  *_authorizedStatKeysList = mm->getAll();
#endif
}

AuthorizedStatKeysList::~AuthorizedStatKeysList()
{
  for (auto it = _authorizedStatKeysList->begin() ; it != _authorizedStatKeysList->end() ; ++it)
    delete *it;
  delete _authorizedStatKeysList;
}

std::list<AuthorizedStatKeys *> const	&AuthorizedStatKeysList::getAuthorizedStatKeysList() const
{
  return (*this->_authorizedStatKeysList);
}

void				AuthorizedStatKeysList::addAuthorizedStatKeys(AuthorizedStatKeys *authorizedStatKeys)
{
  this->_authorizedStatKeysList->push_back(authorizedStatKeys);
}

AuthorizedStatKeys		*AuthorizedStatKeysList::getAuthorizedStatKeys(std::string const &name) const
{
  for (auto it = _authorizedStatKeysList->begin() ; it != _authorizedStatKeysList->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

AuthorizedStatKeys		*AuthorizedStatKeysList::getAuthorizedStatKeys(unsigned int const) const
{
  return (NULL);
}

/*
**
**	AuthorizedStatKeyLoader
**
*/

AuthorizedStatKeyLoader::AuthorizedStatKeyLoader() :
  _authorizedStatKeysList(new AuthorizedStatKeysList)
{

}

AuthorizedStatKeyLoader::~AuthorizedStatKeyLoader()
{
  delete _authorizedStatKeysList;
}

bool				AuthorizedStatKeyLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["AUTHORIZEDSTATKEYSLIST"];
  for (auto it = _authorizedStatKeysList->getAuthorizedStatKeysList().begin() ; it != _authorizedStatKeysList->getAuthorizedStatKeysList().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["AUTHORIZEDSTATKEYSLIST"][(*it)->getName()]));
  return (ret);
}

bool				AuthorizedStatKeyLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  AuthorizedStatKeys		*authorizedStatKey;

  if (trame[CONTENT].isMember("AUTHORIZEDSTATKEYSLIST"))
    {
      auto			members = trame[CONTENT]["AUTHORIZEDSTATKEYSLIST"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  authorizedStatKey = AuthorizedStatKeys::deserialization(trame(trame[CONTENT]["AUTHORIZEDSTATKEYSLIST"][*it]));
	  if (authorizedStatKey)
	    {
	      authorizedStatKey->setName(*it);
	      _authorizedStatKeysList->addAuthorizedStatKeys(authorizedStatKey);
	    }
	}
    }
  return (ret);
}

AuthorizedStatKeysList const			&AuthorizedStatKeyLoader::getLoaderContent() const
{
  return (*_authorizedStatKeysList);
}

AuthorizedStatKeysList::value			*AuthorizedStatKeyLoader::getValue(std::string const &name) const
{
  return (this->_authorizedStatKeysList->getAuthorizedStatKeys(name));
}

AuthorizedStatKeysList::value			*AuthorizedStatKeyLoader::getValue(unsigned int const id) const
{
  return (this->_authorizedStatKeysList->getAuthorizedStatKeys(id));
}

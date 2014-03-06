//
// AuthorizedStatKeysLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 13:55:07 2014 laurent ansel
// Last update Thu Mar  6 14:11:29 2014 laurent ansel
//

#ifndef 			__AUTHORIZEDSTATKEYSLOADER_HH__
# define 			__AUTHORIZEDSTATKEYSLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Stats/AuthorizedStatKeys.hh"

class				AuthorizedStatKeysList
{
public:
  typedef AuthorizedStatKeys	value;

private:
  void				setAuthorizedStatKeysList(std::list<AuthorizedStatKeys *> const &authorizedStatKeysList);

private:
  std::list<AuthorizedStatKeys *>	*_authorizedStatKeysList;

public:
  AuthorizedStatKeysList();
  virtual ~AuthorizedStatKeysList();

  std::list<AuthorizedStatKeys *> const	&getAuthorizedStatKeysList() const;

  void				addAuthorizedStatKeys(AuthorizedStatKeys *authorizedStatKeys);

  AuthorizedStatKeys		*getAuthorizedStatKeys(std::string const &name) const;
  AuthorizedStatKeys		*getAuthorizedStatKeys(unsigned int const id) const;
};

class				AuthorizedStatKeyLoader : public ILoader<AuthorizedStatKeysList>
{
private:
  AuthorizedStatKeysList	*_authorizedStatKeysList;
public:
  AuthorizedStatKeyLoader();
  virtual ~AuthorizedStatKeyLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual AuthorizedStatKeysList const	&getLoaderContent() const;
  virtual AuthorizedStatKeysList::value	*getValue(std::string const &name) const;
  virtual AuthorizedStatKeysList::value	*getValue(unsigned int const id) const;
};

#endif

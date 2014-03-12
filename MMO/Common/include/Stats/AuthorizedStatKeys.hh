//
// AuthorizedStatKeys.hh for AuthorizedStatKeys.hh in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 20 13:26:38 2014 alexis mestag
// Last update Tue Mar 11 16:18:29 2014 alexis mestag
//

#ifndef					__AUTHORIZEDSTATKEYS_HH__
# define				__AUTHORIZEDSTATKEYS_HH__

# include				<list>
# include				"Database/Persistent.hh"
# include				"Stats/StatKey.hh"
# include				"Utility/Nameable.hh"
# include				"Utility/Wrapper.hpp"
# include				"Utility/ISerialization.hh"

class					AuthorizedStatKeys : public Persistent, public Nameable, public ContainerWrapper<std::list<StatKey const *>>, public ISerialization
{
  friend class				odb::access;

public:
  AuthorizedStatKeys();
  AuthorizedStatKeys(AuthorizedStatKeys const &rhs);
  virtual ~AuthorizedStatKeys();

  AuthorizedStatKeys			&operator=(AuthorizedStatKeys const &rhs);

  bool					isAuthorized(StatKey const &key) const;

  bool					addKey(StatKey const &key);
  bool					removeKey(StatKey const &key);

  container_type const			&getKeys() const;
  void					setKeys(container_type const &keys);

  StatKey const				*getKey(std::string const &key) const;

  virtual bool				serialization(Trame &trame) const;
  static AuthorizedStatKeys		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(AuthorizedStatKeys)
#  pragma db member(AuthorizedStatKeys::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(AuthorizedStatKeys::keys) virtual(AuthorizedStatKeys::container_type) get(getContainer()) set(setContainer(?))
# endif

#endif

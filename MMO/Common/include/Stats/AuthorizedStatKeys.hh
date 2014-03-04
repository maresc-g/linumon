//
// AuthorizedStatKeys.hh for AuthorizedStatKeys.hh in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 20 13:26:38 2014 alexis mestag
// Last update Mon Mar  3 14:49:27 2014 alexis mestag
//

#ifndef					__AUTHORIZEDSTATKEYS_HH__
# define				__AUTHORIZEDSTATKEYS_HH__

# include				<list>
# include				"Database/Persistent.hh"
# include				"Stats/StatKey.hh"
# include				"Utility/Nameable.hh"
# include				"Utility/Wrapper.hpp"

class					AuthorizedStatKeys : public Persistent, public Nameable, public ContainerWrapper<std::list<StatKey const *>>
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
};

# ifdef	ODB_COMPILER
#  pragma db object(AuthorizedStatKeys)
#  pragma db member(AuthorizedStatKeys::keys) virtual(AuthorizedStatKeys::container_type) get(getContainer()) set(setContainer(?))
# endif

#endif

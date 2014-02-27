//
// AuthorizedStatKeys.hh for AuthorizedStatKeys.hh in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 20 13:26:38 2014 alexis mestag
// Last update Thu Feb 27 18:17:45 2014 alexis mestag
//

#ifndef					__AUTHORIZEDSTATKEYS_HH__
# define				__AUTHORIZEDSTATKEYS_HH__

# include				<list>
# include				"Database/Persistent.hh"
# include				"Utility/Nameable.hh"
# include				"Stats/StatKey.hh"

class					AuthorizedStatKeys : public Persistent, public Nameable
{
  friend class				odb::access;

public:
  typedef std::list<StatKey const *>	container_type;

private:
  container_type			_keys;

public:
  AuthorizedStatKeys();
  AuthorizedStatKeys(AuthorizedStatKeys const &rhs);
  virtual ~AuthorizedStatKeys();

  AuthorizedStatKeys			&operator=(AuthorizedStatKeys const &rhs);

  bool					isAuthorized(StatKey const &key) const;

  bool					addKey(StatKey const &key);
  bool					removeKey(StatKey const &key);

  container_type const			&getKeys() const;
  StatKey const				*getKey(std::string const &key) const;
};

# ifdef	ODB_COMPILER
#  pragma db object(AuthorizedStatKeys)
# endif

#endif

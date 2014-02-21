//
// StatKey.hh for StatKey in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 19 14:53:12 2014 alexis mestag
// Last update Thu Feb 20 13:00:51 2014 alexis mestag
//

#ifndef				__STATKEY_HH__
# define			__STATKEY_HH__

# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"

class				StatKey : public Persistent, public Nameable
{
  friend class			odb::access;

private:
  StatKey();

public:
  StatKey(std::string const &key);
  StatKey(StatKey const &rhs);
  virtual ~StatKey();

  StatKey			&operator=(StatKey const &rhs);
  bool				operator==(StatKey const &rhs) const;
  bool				operator!=(StatKey const &rhs) const;
};

# ifdef	ODB_COMPILER
#  pragma db object(StatKey)
# endif

#endif

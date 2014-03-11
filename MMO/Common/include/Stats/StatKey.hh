//
// StatKey.hh for StatKey in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 19 14:53:12 2014 alexis mestag
// Last update Tue Mar 11 16:18:36 2014 alexis mestag
//

#ifndef				__STATKEY_HH__
# define			__STATKEY_HH__

# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"

class				StatKey : public Persistent, public Nameable
{
  friend class			odb::access;

private:
  bool				_shortLived;

private:
  StatKey();

public:
  StatKey(std::string const &key, bool const shortLived = true);
  StatKey(StatKey const &rhs);
  virtual ~StatKey();

  StatKey			&operator=(StatKey const &rhs);
  bool				operator==(StatKey const &rhs) const;
  bool				operator!=(StatKey const &rhs) const;

  bool				isShortLived() const;
  void				setShortLived(bool const shortLived);
};

# ifdef	ODB_COMPILER
#  pragma db object(StatKey)
#  pragma db member(StatKey::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
# endif

#endif

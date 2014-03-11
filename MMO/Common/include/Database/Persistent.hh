//
// Persistent.hh for Persistent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:18:34 2013 alexis mestag
// Last update Mon Mar 10 18:04:29 2014 alexis mestag
//

#ifndef			__PERSISTENT_HH__
# define		__PERSISTENT_HH__

# include		<odb/core.hxx>

class			Persistent
{
  friend class		odb::access;

private:
  unsigned long		_persistentId;

protected:
  Persistent();
  Persistent(Persistent const &rhs);

  Persistent		&operator=(Persistent const &rhs);

public:
  virtual ~Persistent();

  unsigned long		getPersistentId() const;
  bool			isPersistent() const;
};

# ifdef	ODB_COMPILER
#  pragma db object(Persistent) abstract
#  pragma db member(Persistent::_persistentId) id auto column("id")
# endif

#endif

//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Tue Dec 10 14:16:21 2013 alexis mestag
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Entities/Type.hh"

class			Mob : public Persistent, public ACharacter
{
  friend class		odb::access;

private:
  Type const		*_type;

private:
  Mob();

public:
  Mob(Mob const &rhs);
  virtual ~Mob();

  Mob			&operator=(Mob const &rhs);

  Type const		&getType() const;
  void			setType(Type const &type);
};

# ifdef	ODB_COMPILER
#  pragma db object(Mob)
#  pragma db member(Mob::_type) not_null column("type_id")
# endif

#endif

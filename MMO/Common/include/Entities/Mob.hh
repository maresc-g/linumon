//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Fri Jan 24 18:46:21 2014 alexis mestag
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Entities/MobModel.hh"

class			Mob : public Persistent, public ACharacter
{
  friend class		odb::access;

private:
  MobModel const	*_model;

private:
  Mob();

public:
  Mob(Mob const &rhs);
  virtual ~Mob();

  Mob			&operator=(Mob const &rhs);

  MobModel const	&getModel() const;
  void			setModel(MobModel const &model);
};

# ifdef	ODB_COMPILER
#  pragma db object(Mob)
#  pragma db member(Mob::_model) not_null column("model_id")
# endif

#endif

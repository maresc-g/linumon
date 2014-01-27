//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Mon Jan 27 13:12:26 2014 laurent ansel
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Entities/MobModel.hh"
# include		"Utility/ISerialization.hh"

class			Mob : public Persistent, public ACharacter, public ISerialization
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
  virtual bool		serialization(Trame &trame) const;
  virtual bool		deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Mob)
#  pragma db member(Mob::_model) not_null column("model_id")
# endif

#endif

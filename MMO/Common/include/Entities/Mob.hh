//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Thu Feb 27 18:47:42 2014 alexis mestag
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Utility/ISerialization.hh"

class			MobModel;
class			Type;

class			Mob : public Persistent, public ACharacter, public ISerialization
{
  friend class		odb::access;

private:
  MobModel const	*_model;

private:
  Mob();

public:
  Mob(Mob const &rhs);
  Mob(MobModel const &model, unsigned int const level);
  virtual ~Mob();

  Mob			&operator=(Mob const &rhs);

  MobModel const	&getModel() const;
  void			setModel(MobModel const &model);

  Type const		&getType() const;

  virtual bool		serialization(Trame &trame) const;
  static Mob		*deserialization(Trame const &trame);
};

# include		"Entities/MobModel.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Mob)
#  pragma db member(Mob::_model) not_null column("model_id")
# endif

#endif

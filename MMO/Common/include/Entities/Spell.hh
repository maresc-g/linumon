//
// Spell.hh for Spell in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 22:32:05 2013 alexis mestag
// Last update Tue Dec 10 14:15:38 2013 alexis mestag
//

#ifndef			__SPELL_HH__
# define		__SPELL_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Entities/Type.hh"

class			Spell : public Persistent, public Nameable
{
  friend class		odb::access;

private:
  Type const		*_type;
  int			_power;

  Spell();

public:
  Spell(Spell const &rhs);
  virtual ~Spell();

  Spell			&operator=(Spell const &rhs);

  Type const		&getType() const;
  void			setType(Type const &type);

  int			getPower() const;
  void			setPower(int const power); // Should this one be private ?
};

# ifdef	ODB_COMPILER
#  pragma db object(Spell)
#  pragma db member(Spell::_type) not_null column("type_id")
#  pragma db member(Spell::_power)
# endif

#endif

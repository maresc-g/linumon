//
// Spell.hh for Spell in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 22:32:05 2013 alexis mestag
// Last update Tue Mar 25 14:42:19 2014 alexis mestag
//

#ifndef			__SPELL_HH__
# define		__SPELL_HH__

# include		"Database/Persistent.hh"
# include		"Effects/EffectLib.hh"
# include		"Entities/Type.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"

class			Mob;
class			BattleParams;

class			Spell : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

public:
  typedef int		power_type;

private:
  Type const		*_type;
  power_type		_power;
  int			_useLimit;
  EffectLib const	*_effectLib;

private:
  Spell();

public:
  Spell(Spell const &rhs);
  virtual ~Spell();

  Spell			&operator=(Spell const &rhs);
# ifdef			SERVER_COMPILATION
  void			operator()(Mob &cast, Mob &target, BattleParams &battle);
# endif
  Type const		&getType() const;
  void			setType(Type const &type);

  power_type		getPower() const;
  void			setPower(power_type const power);

  int			getUseLimit() const;
  void			setUseLimit(int const useLimit);
  virtual bool		serialization(Trame &trame) const;
  static Spell		*deserialization(Trame const &trame);
};

# include		"Entities/Mob.hh"
# include		"Battle/BattleParams.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Spell)
#  pragma db member(Spell::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Spell::_type) not_null
#  pragma db member(Spell::_power)
#  pragma db member(Spell::_useLimit)
#  pragma db member(Spell::_effectLib) not_null
# endif

#endif

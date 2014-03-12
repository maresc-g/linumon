//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Mar 11 21:37:13 2014 alexis mestag
//

#ifndef 		__CONSUMABLE_HH__
# define 		__CONSUMABLE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Effects/EffectLib.hh"
# include		"Entities/Mob.hh"

class			Consumable : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef enum		eConsumable
    {
      NONE,
      VITA
    }			eConsumable;
private:
  eConsumable		_consumableType;
# ifndef		CLIENT_COMPILATION
  EffectLib const	*_effectLib;
# endif

protected:
  Consumable();
  Consumable(std::string const &name, eConsumable const consumableType);

  Consumable		&operator=(Consumable const &rhs);

  Consumable::eConsumable	getConsumableType() const;
  void			setConsumableType(eConsumable const consumableType);

# ifndef		CLIENT_COMPILATION
  void			setEffectLib(EffectLib const &effectLib);
# endif

public:
  Consumable(Consumable const &rhs);
  virtual ~Consumable();

# ifndef		CLIENT_COMPILATION
  EffectLib const	&getEffectLib() const;

  void			applyEffect(Mob &mob) const;
# endif

  virtual bool		serialization(Trame &trame) const;
  static Consumable	*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Consumable)
#  pragma db member(Consumable::_consumableType) transient
#  pragma db member(Consumable::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Consumable::_effectLib) not_null
# endif

#endif

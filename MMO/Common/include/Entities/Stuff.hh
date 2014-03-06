//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Thu Mar  6 11:47:40 2014 laurent ansel
//

#ifndef 		__STUFF_HH__
# define 		__STUFF_HH__

# include		<map>
# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# ifndef		CLIENT_COMPILATION
# include		"Effects/StatEntityEffect.hh"
# include		"Effects/EffectLib.hh"
#endif
#include		"Stats/Stat.hh"

class			Equipment;

class			Stuff : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef std::map<StatKey const *, Stat::value_type>	effect_type;

public:
  typedef enum		eStuff
    {
      NONE,
      HELMET,
      SHOULDERS,
      RING,
      NECKLACE,
      BOOTS,
      CLOAK,
      BELT,
      BREASTPLATE,
      WEAPON
    }			eStuff;
private:
  eStuff		_stuffType;
  std::map<StatKey const *, Stat::value_type>	*_effect;
# ifndef		CLIENT_COMPILATION
  EffectLib const	*_effectLib;
# endif

private:
# ifndef		CLIENT_COMPILATION
  void			setEffectLib(EffectLib const &effectLib);
# endif

protected:
  Stuff();
  Stuff(std::string const &name, eStuff const stuffType);

  Stuff			&operator=(Stuff const &rhs);

  void			setStuffType(eStuff const stuffType);

public:
  Stuff(Stuff const &rhs);

  virtual ~Stuff();

  Stuff::eStuff		getStuffType() const;

# ifndef		CLIENT_COMPILATION
  EffectLib const	&getEffectLib() const;

  void			applyEffect(AStatEntity &statEntity) const;
# endif

  std::map<StatKey const *, Stat::value_type> const	&getEffect() const;
  void			setEffect(std::map<StatKey const *, Stat::value_type> const &effect);

  virtual bool		serialization(Trame &trame) const;
  static Stuff		*deserialization(Trame const &trame, bool const client = true);
};

# include		"Entities/ACharacter.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Stuff)
#  pragma db member(Stuff::_effect) transient
// #  pragma db member(Stuff::effect) virtual(Stuff::effect_type) get(getEffect()) set(setEffect(?))
# endif

#endif

//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Mar 11 21:45:54 2014 alexis mestag
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
#include		"Stats/Stats.hh"

class			Equipment;

class			Stuff : public Persistent, public AItem
{
  friend class		odb::access;

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
  Stats 		*_stats;

protected:
  Stuff();
  Stuff(std::string const &name, eStuff const stuffType);

  Stuff			&operator=(Stuff const &rhs);

  void			setStuffType(eStuff const stuffType);

public:
  Stuff(Stuff const &rhs);

  virtual ~Stuff();

  Stuff::eStuff		getStuffType() const;

  Stats const		&getStats() const;
  void			setStats(Stats const &stats);

  virtual bool		serialization(Trame &trame) const;
  static Stuff		*deserialization(Trame const &trame, bool const client = true);
};

# include		"Entities/ACharacter.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Stuff)
#  pragma db member(Stuff::_stats) transient
#  pragma db member(Stuff::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Stuff::stats) virtual(Stats::container_type) get(_stats->getContainer()) set(_stats->setContainer(?)) value_not_null
# endif

#endif

//
// Faction.hh for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:28:40 2013 alexis mestag
// Last update Thu Mar 13 19:45:38 2014 alexis mestag
//

#ifndef			__FACTION_HH__
# define		__FACTION_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"
# include		"Effects/EffectLib.hh"

# define		FACTION1	"Hesode"
# define		FACTION2	"Celestia"

class			Player;

class			Faction : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:

# ifndef		CLIENT_COMPILATION
  EffectLib const	*_effectLib;
# endif

private:
  Faction();

# ifndef		CLIENT_COMPILATION
  void			setEffectLib(EffectLib const &effectLib);
# endif

public:
  Faction(std::string const &name);
  Faction(Faction const &rhs);

  Faction		&operator=(Faction const &rhs);

# ifndef		CLIENT_COMPILATION
  EffectLib const	&getEffectLib() const;

  void			applyEffect(Player &player) const;
# endif

public:
  virtual ~Faction();
  virtual bool			serialization(Trame &trame) const;
  static Faction		*deserialization(Trame const &trame);
};

# include		"Entities/Player.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Faction)
#  pragma db member(Faction::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Faction::_effectLib) not_null
# endif

#endif

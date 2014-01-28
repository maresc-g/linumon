//
// Faction.hh for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:28:40 2013 alexis mestag
// Last update Sun Jan 26 14:09:33 2014 laurent ansel
//

#ifndef			__FACTION_HH__
# define		__FACTION_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"

class			Faction : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  Faction(std::string const &name = "");
  Faction(Faction const &rhs);

  Faction		&operator=(Faction const &rhs);

public:
  virtual ~Faction();
  virtual bool			serialization(Trame &trame);
  virtual bool			deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Faction)
# endif

#endif

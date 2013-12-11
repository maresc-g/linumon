//
// Faction.hh for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:28:40 2013 alexis mestag
// Last update Tue Dec 10 15:03:49 2013 alexis mestag
//

#ifndef			__FACTION_HH__
# define		__FACTION_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"

class			Faction : public Persistent, public Nameable
{
  friend class		odb::access;
private:
  Faction(std::string const &name = "");

public:
  Faction(Faction const &rhs);
  virtual ~Faction();

  Faction		&operator=(Faction const &rhs);
};

# ifdef	ODB_COMPILER
#  pragma db object(Faction)
# endif

#endif

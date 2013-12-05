//
// Faction.hh for Faction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:28:40 2013 alexis mestag
// Last update Thu Nov 28 23:30:51 2013 alexis mestag
//

#ifndef			__FACTION_HH__
# define		__FACTION_HH__

# include		"Entities/AStatEntities.hh"

class			Faction : public AStatEntity
{
public:
  Faction();
  Faction(Faction const &rhs);
  virtual ~Faction();

  Faction		&operator=(Faction const &rhs);
};

#endif

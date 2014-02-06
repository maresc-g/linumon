//
// Zone.hh for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:55:50 2014 antoine maitre
// Last update Thu Feb  6 15:07:00 2014 antoine maitre
//

#ifndef			__ZONE_HH__
# define		__ZONE_HH__

# include		<sstream>
# include		<string>
# include		"Trame/Trame.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/GenericSerialization.hpp"

namespace		ZONE
{
  enum			eZone
    {
      NONE,
      PLAIN,
      ROCK
    };
};

# include		"Case.hh"

class			Case;

class			Zone : public ISerialization
{
private:
  int const		_sizeX;
  int const		_sizeY;
  std::list<AEntity *>	*_players;
  ZONE::eZone const	_type;
  std::list<Case *>	*_cases;
public:
  Zone(Json::Value topography);
  Zone(int const, int const, ZONE::eZone const);
  virtual ~Zone();
  void			addPlayer(AEntity *);
  void			delPlayer(AEntity *);
  std::list<AEntity*>	&getPlayers() const;
  void			addCase(Case *);
  void			delCase(Case *);
  Case			*getCase(int const, int const) const;
  std::list<Case *>	*getCases() const;
  virtual bool		serialization(Trame &trame) const;
  void			deserialization(Trame const &trame);
};

bool			sameValue(Case *, Case *);
bool			compareValue(Case *case1, Case *case2);

#endif

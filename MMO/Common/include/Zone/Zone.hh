//
// Zone.hh for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:55:50 2014 antoine maitre
// Last update Tue Jan 28 14:47:37 2014 laurent ansel
//

#ifndef			__ZONE_HH__
# define		__ZONE_HH__

# include		<sstream>
# include		<string>
# include		"Case.hh"
# include		"Trame/Trame.hh"
# include		"Utility/Nameable.hh"

class			Zone : public Nameable
{
public :
  enum			eZone
    {
      PLAIN,
      ROCK
    };
private:
  int const		_sizeX;
  int const		_sizeY;
  std::list<AEntity *>	*_players;
  eZone const		_type;
  std::list<Case *>	*_cases;
public:
  Zone(Json::Value topography);
  virtual ~Zone();
  void			addPlayer(AEntity *);
  void			delPlayer(AEntity *);
  std::list<AEntity*>	&getPlayers() const;
  void			addCase(Case *);
  void			delCase(Case *);
  Case			*getCase(int const, int const);
  std::list<Case *>	&getCases() const;
};

bool			sameValue(Case *, Case *);
bool			compareValue(Case *case1, Case *case2);

#endif

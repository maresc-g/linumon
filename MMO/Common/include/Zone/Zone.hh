//
// Zone.hh for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:55:50 2014 antoine maitre
// Last update Thu Mar 13 12:02:08 2014 antoine maitre
//

#ifndef			__ZONE_HH__
# define		__ZONE_HH__

# include		<sstream>
# include		<string>
# include		"Trame/Trame.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/GenericSerialization.hpp"
# include		"Entities/Player.hh"
# include		"Entities/Ressource.hh"
# include		"Case.hh"
# include		"Mutex/MutexVar.hpp"
# include		"Map/Map.hh"

# ifdef	SERVER
#  include		"Database/Repositories/DBZoneRepository.hpp"
# endif

class			Case;
class			Player;

class			Zone : public ISerialization, public Nameable
{
private:
  int const		_sizeX;
  int const		_sizeY;
  int const		_posX;
  int const		_posY;
  std::list<AEntity *>	*_players;
  std::list<Case *>	*_cases;

# ifdef	SERVER
  DBZone const		*_dbZone;

  void			setDBZone(DBZone const &zone);
# endif

public:
  Zone(Json::Value topography);
  //  Zone(int const, int const, std::string const);
  virtual ~Zone();
  void			cleanEntity(AEntity *entity);
  void			addPlayer(AEntity *);
  void			delPlayer(AEntity *);
  void			addEntity(AEntity *entity);
  void			delEntity(AEntity *entity);
  void			delEntity(unsigned int const id, Ressource::RessourceCoordinate const &coord);
  std::list<AEntity*>	&getPlayers() const;
  void			addCase(Case *);
  void			delCase(Case *);
  Case			*getCase(int const, int const) const;
  std::list<Case *>	*getCases() const;
  virtual bool		serialization(Trame &trame) const;
  void			deserialization(Trame const &trame);
  bool			move(AEntity *entity);
  int			getSizeX() const;
  int			getSizeY() const;
  int			getPosX() const;
  int			getPosY() const;
# ifdef	SERVER
  DBZone const		&getDBZone() const;
# endif
};

bool			sameValue(Case *, Case *);
bool			compareValue(Case *case1, Case *case2);

#endif

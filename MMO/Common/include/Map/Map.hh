
//
// Map.hh for MAP in /home/maitre_c/work/linumon/MMO/Server/include/Map
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:31:09 2014 antoine maitre
// Last update Mon Feb 10 15:34:42 2014 antoine maitre
//

#ifndef					__MAP_HH__
# define				__MAP_HH__

# include				<map>
# include				"Zone/Zone.hh"
# include				"Utility/Singleton.hpp"
# include				"Mutex/Mutex.hpp"
# include				"Entities/AEntity.hh"

class					Map : public Singleton<Map>
{
  friend class				Singleton<Map>;
private:
  std::map<std::string const, Zone*>	_map;
  Mutex					*_mutex;
  Map();
  virtual ~Map();
public:
  Zone					*getZone(std::string const);
  void					delPlayer(std::string const &zone, AEntity *entity);
  void					addEntity(std::string const &zone, AEntity *entity);
  void					moveZone(std::string const &source, std::string const &dest, AEntity *);
  std::list<AEntity *>			*getPlayers(std::string const &zone);
  void					moveCase(std::string const &zone, Player::PlayerCoordinate const &x, Player::PlayerCoordinate const &y, AEntity *);
  void					lock() const;
  void					unlock() const;
};

#endif

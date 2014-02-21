//
// Map.hh for MAP in /home/maitre_c/work/linumon/MMO/Server/include/Map
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:31:09 2014 antoine maitre
// Last update Fri Feb 21 15:34:54 2014 guillaume marescaux
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
  void					delPlayer(std::string const &zone, AEntity *player);
  void					addPlayer(std::string const &zone, AEntity *player);
  void					delEntity(std::string const &zone, AEntity *player);
  void					delEntity(std::string const &zone, unsigned int const id, Ressource::RessourceCoordinate const &coord);
  void					addEntity(std::string const &zone, AEntity *player);
  // void					delEntity(std::string const &zone, AEntity *entity);
  // void					addEntity(std::string const &zone, AEntity *entity);
  void					changeZone(std::string const &source, std::string const &dest, AEntity *);
  std::list<AEntity *>			*getPlayers(std::string const &zone);
  void					move(AEntity *entity);
  //  void					moveCase(std::string const &zone, Player::PlayerCoordinate const &source, Player::PlayerCoordinate const &dest, AEntity *);
  void					lock() const;
  void					unlock() const;
  AEntity				*getEntityById(std::string const &zone, unsigned int const id);
  Player				*getPlayerById(unsigned int const id);
};

#endif

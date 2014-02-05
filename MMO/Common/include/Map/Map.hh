//
// Map.hh for MAP in /home/maitre_c/work/linumon/MMO/Server/include/Map
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:31:09 2014 antoine maitre
// Last update Wed Feb  5 16:52:22 2014 antoine maitre
//

#ifndef				__MAP_HH__
# define			__MAP_HH__

# include			<map>
# include			"Zone/Zone.hh"
# include			"Utility/Singleton.hpp"
# include			"Mutex/Mutex.hpp"

class				Map : public Singleton<Map>, public Mutex
{
  friend class			Singleton<Map>;
  std::map<ZONE::eZone const, Zone*>	_map;
  Mutex				*_mutex;
private:
  Map();
  virtual ~Map();
public:
  Zone				*getZone(ZONE::eZone const);
  void				lock() const;
  void				unlock() const;
};

#endif

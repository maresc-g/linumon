//
// Map.hh for MAP in /home/maitre_c/work/linumon/MMO/Server/include/Map
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:31:09 2014 antoine maitre
// Last update Tue Jan 28 12:03:06 2014 antoine maitre
//

#ifndef				__MAP_HH__
# define			__MAP_HH__

# include			<map>
# include			"Zone/Zone.hh"
# include			"Utility/Singleton.hpp"

class				Map : public Singleton<Map>
{
  friend class			Singleton<Map>;
  std::map<Zone::eZone const, Zone*>	_map;
private:
  Map();
  virtual ~Map();
public:
  Zone				*getZone(Zone::eZone const);
};

#endif

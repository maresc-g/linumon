//
// Map.cpp for toto in /home/maitre_c/work/linumon/MMO/Server/include
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 16:29:17 2014 antoine maitre
// Last update Mon Feb  3 13:50:16 2014 antoine maitre
//

#include			"Map/Map.hh"

Map::Map()
{
  std::string			fileConf;
  Trame				tram;
  std::ostringstream		terr;

  for (int i = 1; i; i++)
    {
      terr << "Territory" << i;
      if (tram.isMember(terr.str()))
	_map.insert(std::make_pair(static_cast<const Zone::eZone>(tram[terr.str()]["Type"].asInt()), new Zone(tram[terr.str()])));
      else
	break;
      terr.str("");
    }
}

Map::~Map()
{

}

Zone				*Map::getZone(Zone::eZone const type)
{
  return (this->_map[type]);
}


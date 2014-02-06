//
// Map.cpp for toto in /home/maitre_c/work/linumon/MMO/Server/include
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 16:29:17 2014 antoine maitre
// Last update Thu Feb  6 11:07:23 2014 guillaume marescaux
//

#include			"Map/Map.hh"

Map::Map()
  : _mutex(new Mutex)
{
  std::string			fileConf = "Res/Map.json";
  JsonFile			file;
  Trame				tram;
  std::ostringstream		terr;
  

  this->_mutex->init();
  JsonFile::readFile(tram, fileConf);
  for (int i = 1; i; i++)
    {
      terr << "Territory" << i;
      if (tram.isMember(terr.str()))
	{
	  _map.insert(std::make_pair(static_cast<const ZONE::eZone>(tram[terr.str()]["Type"].asInt()), new Zone(tram[terr.str()])));
	}
      else
	break;
      terr.str("");
    }
}

Map::~Map()
{
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
    delete (*it).second;
  delete _mutex;
}

Zone				*Map::getZone(ZONE::eZone const type)
{
  return (this->_map[type]);
}

void				Map::lock() const
{
  this->_mutex->lock();
}

void				Map::unlock() const
{
  this->_mutex->unlock();
}

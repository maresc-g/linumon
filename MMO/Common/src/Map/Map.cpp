//
// Map.cpp for toto in /home/maitre_c/work/linumon/MMO/Server/include
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 16:29:17 2014 antoine maitre
// Last update Mon Feb 10 15:34:03 2014 antoine maitre
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
	  _map.insert(std::make_pair(tram[terr.str()]["Type"].asString(), new Zone(tram[terr.str()])));
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

Zone				*Map::getZone(std::string const name)
{
  return (this->_map[name]);
}

void				Map::lock() const
{
  this->_mutex->lock();
}

void				Map::unlock() const
{
  this->_mutex->unlock();
}

void				Map::delPlayer(std::string const &zone, AEntity *entity)
{
  this->lock();
  this->_map[zone]->delPlayer(entity);
  this->unlock();
}

void				Map::addEntity(std::string const &zone, AEntity *entity)
{
  this->lock();
  this->_map[zone]->addPlayer(entity);
  this->unlock();
}

std::list<AEntity *>		*Map::getPlayers(std::string const &zone)
{
  this->lock();
  std::list<AEntity*> *list = &this->_map[zone]->getPlayers();
  this->unlock();
  return (list);
}

void				Map::moveZone(std::string const &source, std::string const &dest, AEntity *entity)
{
  this->lock();
  this->_map[source]->delPlayer(entity);
  this->_map[dest]->addPlayer(entity);
  this->unlock();
}

void				Map::moveCase(std::string const &zone, Player::PlayerCoordinate const &source, Player::PlayerCoordinate const &dest, AEntity *entity)
{
  this->lock();
  this->_map[zone]->move(source, dest, entity);
  this->unlock();
}


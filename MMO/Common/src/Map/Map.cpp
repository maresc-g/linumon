//
// Map.cpp for toto in /home/maitre_c/work/linumon/MMO/Server/include
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 16:29:17 2014 antoine maitre
// Last update Mon Feb 17 14:49:49 2014 antoine maitre
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
	  _map.insert(std::make_pair(tram[terr.str()]["Name"].asString(), new Zone(tram[terr.str()])));
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

Zone				*Map::getZone(std::string const zone)
{
  if (this->_map.find(zone) != this->_map.end())
    return (this->_map[zone]);
  else
    return (NULL);
}

void				Map::lock() const
{
  this->_mutex->lock();
}

void				Map::unlock() const
{
  this->_mutex->unlock();
}

void				Map::delPlayer(std::string const &zone, AEntity *player)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->delPlayer(player);
  this->unlock();
}

void				Map::addPlayer(std::string const &zone, AEntity *player)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->addPlayer(player);
  this->unlock();
}

void				Map::addEntity(std::string const &zone, AEntity *entity)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->addEntity(entity);
  this->unlock();
}

void				Map::delEntity(std::string const &zone, AEntity *entity)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->delEntity(entity);
  this->unlock();
}

// void				Map::addEntity(std::string const &zone, AEntity *entity)
// {
//   this->lock();
//   if (this->_map.find(zone) != this->_map.end())
//     this->_map[zone]->addEntity(player);
//   this->unlock();
// }

// void				Map::delEntity(std::string const &zone, AEntity *entity)
// {
//   this->lock();
//   if (this->_map.find(zone) != this->_map.end())
//     this->_map[zone]->delEntity(player);
//   this->unlock();
// }

std::list<AEntity *>		*Map::getPlayers(std::string const &zone)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    {
      std::list<AEntity*> *list = &this->_map[zone]->getPlayers();
      this->unlock();
      return (list);
    }
  else
    return (NULL);
}

void				Map::moveZone(std::string const &source, std::string const &dest, AEntity *entity)
{
  this->lock();
  if (this->_map.find(source) != this->_map.end() &&
      this->_map.find(dest) != this->_map.end())
    {
      this->_map[source]->delPlayer(entity);
      this->_map[dest]->addPlayer(entity);
    }
  this->unlock();
}

void				Map::moveCase(std::string const &zone, Player::PlayerCoordinate const &source, Player::PlayerCoordinate const &dest, AEntity *entity)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->move(source, dest, entity);
  this->unlock();
}


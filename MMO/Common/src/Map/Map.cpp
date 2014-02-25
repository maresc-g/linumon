//
// Map.cpp for toto in /home/maitre_c/work/linumon/MMO/Server/include
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 16:29:17 2014 antoine maitre
// Last update Tue Feb 25 17:09:12 2014 laurent ansel
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
  this->_mutex->lock();
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
  this->_mutex->unlock();
}

Map::~Map()
{
  this->_mutex->lock();
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
    delete (*it).second;
  this->_mutex->unlock();
  _mutex->destroy();
  delete _mutex;
}

Zone				*Map::getZoneByPos(int const x, int const y)
{
  std::cout << x << " " << y << std::endl;
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
    {
      std::cout << (*it).second->getPosX() << " " << (*it).second->getPosY() << std::endl;
      if ((*it).second->getPosX() == x && (*it).second->getPosY() == y)
	return ((*it).second);
    }
  std::cout << "Je suis un connard" << std::endl;
  return (NULL);
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

void				Map::delEntity(std::string const &zone, unsigned int const id, Ressource::RessourceCoordinate const &coord)
{
  this->lock();
  if (this->_map.find(zone) != this->_map.end())
    this->_map[zone]->delEntity(id, coord);
  this->unlock();
}

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
    {
      this->unlock();
      return (NULL);
    }
}

Player				*Map::getPlayerById(unsigned int const id)
{
  this->lock();
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
    {
      for (auto itb = (*it).second->getPlayers().begin(); itb != (*it).second->getPlayers().end(); itb++)
	{
	  if ((*itb)->getId() == id)
	    {
	      this->unlock();
	      return (static_cast<Player *>(*itb));
	    }
	}
    }
  this->unlock();
  return (NULL);
}

void				Map::changeZone(std::string const &source, std::string const &dest, AEntity *entity)
{
  if (this->_map.find(source) != this->_map.end() &&
      this->_map.find(dest) != this->_map.end())
    {
      this->_map[source]->delPlayer(entity);
      this->_map[dest]->addPlayer(entity);
    }
}

bool				Map::move(AEntity *entity)
{
  bool				ret;

  this->lock();
  if (this->_map.find(static_cast<Player *>(entity)->getZone()) != this->_map.end())
    std::cout << "ZONE FOUND = " << static_cast<Player *>(entity)->getZone() << std::endl;
  else
    std::cout << "ZONE NOT FOUND = " << static_cast<Player *>(entity)->getZone() << std::endl;
  ret = this->_map[static_cast<Player *>(entity)->getZone()]->move(entity);
  this->unlock();
  return (ret);
}

AEntity				*Map::getEntityById(std::string const &zone, unsigned int id)
{
  this->lock();
  // for (auto it = this->_map.begin(); it != this->_map.end(); it++)
  //   {
  //     for (auto itb = (*it).second->getPlayers().begin(); itb != (*it).second->getPlayers().end(); itb++)
  // 	if ((*itb)->getId() == id)
  // 	  {
  // 	    this->unlock();
  // 	    return (true);
  // 	  }
  //   }

  for (auto it = this->_map[zone]->getCases()->begin() ; it != this->_map[zone]->getCases()->end() ; it++)
    {
      for (auto itb = (*it)->getEntities()->begin() ; itb != (*it)->getEntities()->end() ; itb++)
  	{
  	  if ((*itb)->getId() == id)
  	    {
  	      this->unlock();
  	      return (*itb);
  	    }
  	}
    }
  this->unlock();
  return (NULL);
}

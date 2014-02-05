//
// Map.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 11:17:06 2014 guillaume marescaux
// Last update Wed Feb  5 14:11:42 2014 guillaume marescaux
//

#include			"Map/Map.hh"

Map::Map():
  _mutex(new Mutex),
  _zone(NULL)
{
  _mutex->init();
}

Map::~Map()
{
  delete _mutex;
  delete _zone;
}

void				Map::setZone(Zone *zone)
{
  if (zone)
    _zone = zone;
}

void				Map::lock(void)
{
  _mutex->lock();
}

void				Map::unlock(void)
{
  _mutex->unlock();
}

Zone const			&Map::getZone(void) const
{
  return (*_zone);
}

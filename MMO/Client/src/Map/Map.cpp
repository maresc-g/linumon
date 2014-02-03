//
// Map.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 11:17:06 2014 guillaume marescaux
// Last update Mon Feb  3 12:30:16 2014 guillaume marescaux
//

#include			"Map/Map.hh"

Map::Map():
  _mutex(new Mutex)
  // _zone(new Zone)
{
  _mutex->init();
}

Map::~Map()
{
  delete _mutex;
  // delete _zone;
}

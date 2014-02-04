//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Mon Feb  3 13:06:55 2014 cyril jourdain
//

#include		<iostream>
#include		"Client.hh"
#include		"Map/Map.hh"

int			main(int ac, char **av)
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  Client		*client = Client::getInstance();
  Map::getInstance();

  client->init(ac, av);
  client->deleteInstance();
  return (0);
}

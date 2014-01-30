//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Thu Jan 30 12:35:05 2014 guillaume marescaux
//

#include		<iostream>
#include		"Client.hh"
#include <unistd.h>

int			main()
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  Client		*client = Client::getInstance();

  client->deleteInstance();
  return (0);
}

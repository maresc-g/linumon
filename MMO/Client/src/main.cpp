//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Thu Jan 30 15:47:33 2014 guillaume marescaux
//

#include		<iostream>
#include		"Client.hh"

int			main(int ac, char **av)
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  Client		*client = Client::getInstance();
  // WindowManager         *manager = new WindowManager(ac, av);

  // manager->exec();

  client->init(ac, av);
  client->deleteInstance();
  return (0);
}

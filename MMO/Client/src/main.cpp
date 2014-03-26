//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Wed Mar 26 15:05:34 2014 cyril jourdain
//

#include		<iostream>
#include		"Client.hh"
#include		<stdexcept>
#include		"Map/Map.hh"
#include		"Error/SocketError.hpp"

int			main(int ac, char **av)
{
  try
    {
      ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
      ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
      Client		*client = Client::getInstance();
      Map::getInstance();

      client->init(ac, av);
      client->deleteInstance();
    }
  catch (std::invalid_argument e)
    {
      std::cerr << "Error : Bad arguments" << std::endl;
      return (1);
    }
  catch (SocketError const &e)
    {
      std::cerr << "Error : Error socket" << std::endl;
      return (2);
    }
  return (0);
}

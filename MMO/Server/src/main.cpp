//
// main.cpp for  in /home/ansel_l/Documents/Pfa/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:45:53 2013 laurent ansel
// Last update Mon Mar  3 16:03:35 2014 alexis mestag
//

#include		<string>
#include		<iostream>
#include		<sstream>
#include		<stdexcept>
#include		<stdlib.h>
#include		<ctime>
#include		"Server/Server.hh"
#include		"Error/SocketError.hpp"
#include		"CodeBreaker/CodeBreaker.hh"

#include		"Database/Repositories/Repository.hpp"
#include		"Entities/Mob.hh"

int			main(int argc, char **argv)
{
  Trame			trame;
  int			ret = 0;

  if (argc == 2)
    {
      try
  	{
  	  int			port = std::stoi(argv[1]);

  	  srand(time(NULL));
  	  Server::getInstance()->init(port);
  	  // Server::getInstance()->run();

	  Repository<Player>	*rp = &Database::getRepository<Player>();
	  Player		*p = rp->getById(1);
	  Mob			*m;

	  std::cout << p->getName() << std::endl;
	  for (auto it = p->getDigitaliser().begin() ; it != p->getDigitaliser().end() ; ++it) {
	    m = *it;
	    std::cout << "\t" << m->getName() << std::endl;
	    for (auto jt = m->getModel().getSpells().begin() ; jt != m->getModel().getSpells().end() ; ++jt) {
	      std::cout << "\t\t" << (*jt)->getName() << std::endl;
	    }
	  }

	  delete p;

  	  Server::deleteInstance();
  	}
      catch (std::invalid_argument const &e)
  	{
  	  std::cerr << "Invalid port" << std::endl;
  	  ret = 2;
  	}
      catch (SocketError const &e)
  	{
  	  std::cerr << e.what() << std::endl;
  	  ret = 3;
  	}
    }
  else
    {
      std::cerr << "Usage:\n\t" << argv[0] << " [port]" << std::endl;
      ret = 1;
    }
  return (ret);
}

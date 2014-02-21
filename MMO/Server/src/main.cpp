//
// main.cpp for  in /home/ansel_l/Documents/Pfa/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:45:53 2013 laurent ansel
// Last update Fri Feb 21 00:48:21 2014 alexis mestag
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

int			main()
{
  Repository<Mob>			*rmm = &Database::getInstance()->getRepository<Mob>();
  auto					mms = rmm->getAll();

  std::cout << "Size : " << mms.size() << " (" << mms.empty() << ")" << std::endl;
  if (!mms.empty()) {
    for (auto jt = mms.begin() ; jt != mms.end() ; ++jt) {
      MobModel const			*mm = &(*jt)->getModel();

      std::cout << mm->getName() << std::endl;
      for (auto it = mm->getStats().getStats().cbegin() ; it != mm->getStats().getStats().cend() ; ++it)
	{
	  std::cout << "\t" << (*it)->getKey().getName() << " : " << (*it)->getValue() << std::endl;
	}
    }
  }

  Repository<MobModel>::deleteInstance();
  Database::deleteInstance();
  return (0);
}

// int			main(int argc, char **argv)
// {
//   Trame			trame;

//   int			ret = 0;

//   if (argc == 2)
//     {
//       try
//   	{
//   	  int			port = std::stoi(argv[1]);

//   	  srand(time(NULL));
//   	  Server::getInstance()->init(port);
//   	  Server::getInstance()->run();
//   	  Server::deleteInstance();
//   	}
//       catch (std::invalid_argument const &e)
//   	{
//   	  std::cerr << "Invalid port" << std::endl;
//   	  ret = 2;
//   	}
//       catch (SocketError const &e)
//   	{
//   	  std::cerr << e.what() << std::endl;
//   	  ret = 3;
//   	}
//     }
//   else
//     {
//       std::cerr << "Usage:\n\t" << argv[0] << " [port]" << std::endl;
//       ret = 1;
//     }
//   return (ret);
// }

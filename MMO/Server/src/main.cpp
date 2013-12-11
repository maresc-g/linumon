//
// main.cpp for  in /home/ansel_l/Documents/Pfa/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:45:53 2013 laurent ansel
// Last update Tue Dec 10 14:03:00 2013 alexis mestag
//

#include		<string>
#include		<iostream>
#include		<sstream>
#include		<stdexcept>
#include		<stdlib.h>
#include		<ctime>
#include		"Server/Server.hh"
#include		"Error/SocketError.hpp"

#include                <odb/session.hxx>
#include                <odb/database.hxx>
#include                <odb/transaction.hxx>
#include                <odb/mysql/database.hxx>

#include		"Entities/Player-odb.hxx"
#include		"Entities/Type-odb.hxx"

void			test(odb::database *const db)
{
  {
    odb::transaction	t(db->begin());
    Type		*type = db->load<Type>(2);
    Type		*type2 = db->load<Type>(1);

    std::cout << type->getName() << std::endl;
    for (auto it = type->getRelations().getRelations().cbegin() ;
    	 it != type->getRelations().getRelations().cend() ;
    	 ++it) {
      // std::cout << "\t- " << (void *)it->first << std::endl;
      std::cout << "\t- " << it->type->getName() << " : " << it->coeff << std::endl;
    }
    std::cout << "Size " << type->getRelations().getRelations().size() << std::endl;
    t.commit();
    delete type;
    delete type2;
  }
}

int			main()
{
  int                   ret = 0;

  try
    {
      odb::database     *db = new odb::mysql::database("mmoUser", "mmoPassword", "mmo");

      odb::session      s;

      test(db);

      delete db;
    }
  catch (odb::exception const &e)
    {
      std::cerr << e.what() << std::endl;
      ret = 1;
    }
  return (ret);
}

// int			main(int argc, char **argv)
// {
//   int			ret = 0;

//   if (argc == 2)
//     {
//       try
//   	{
//   	  int			port = std::stoi(argv[1]);
//   	  Server		*server = new Server(port);

//   	  srand(time(NULL));
//   	  server->run();
//   	  delete server;
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

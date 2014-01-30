//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Thu Jan 30 13:49:18 2014 cyril jourdain
//

#include		<iostream>
#include		"Client.hh"
#include	        "SFML/SFMLView.hpp"
#include	        "Qt/WindowManager.hh"
#include	        "Qt/LoginView/LoginView.hh"
#include	        <Qt/qapplication.h>
#include	        <Qt/qframe.h>
#include	        <Qt/qpushbutton.h>
#include	        <Qt/qfile.h>
#include	        <Qt/qgridlayout.h>

int			main(int ac, char **av)
{
  // ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  // ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  // Client		*client = Client::getInstance();
  WindowManager         *manager = new WindowManager(ac, av);

  manager->exec();

  // client->deleteInstance();
  return (0);
}

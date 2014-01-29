//
// main.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO/Client
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 11:16:43 2014 guillaume marescaux
// Last update Wed Jan 29 15:37:59 2014 guillaume marescaux
//

#include		<iostream>
#include		"Client.hh"
#include <unistd.h>

int			main()
{
  Client		*client = Client::getInstance();

  client->deleteInstance();
  return (0);
}

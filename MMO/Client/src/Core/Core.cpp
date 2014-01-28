//
// Core.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:58:09 2014 guillaume marescaux
// Last update Fri Jan 24 15:19:22 2014 guillaume marescaux
//

#include		"Core/Core.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Core::Core():
  _sockets(new std::map<eSocket, Socket *>),
  _socketsClient(new std::map<eSocket, ISocketClient *>),
  _infos(new ConnectionInfos),
  _player(NULL),
  _poll(new Poll)
{
  (*_sockets)[TCP] = new Socket;
  (*_sockets)[UDP] = new Socket;
  (*_socketsClient)[TCP] = NULL;
  (*_socketsClient)[UDP] = NULL;

  Trame *trame = new Trame();
  Trame::readFile(*trame, "Res/Connection.json");
  _infos->ip = (*trame)["ip"].asString();
  _infos->port = (*trame)["port"].asInt();
  delete trame;

  (*_sockets)[TCP]->initialize("TCP");
  (*_sockets)[UDP]->initialize("UDP");
  (*_socketsClient)[TCP] = (*_sockets)[TCP]->connectToAddr(_infos->ip, _infos->port);
  (*_socketsClient)[UDP] = (*_sockets)[UDP]->connectToAddr(_infos->ip, _infos->port);
}

Core::~Core()
{
  delete _infos;
  (*_sockets)[TCP]->destroy();
  (*_sockets)[UDP]->destroy();
  delete (*_sockets)[TCP];
  delete (*_sockets)[UDP];
  delete _sockets;
  delete _socketsClient;
  delete _player;
  delete _poll;
}

//------------------------------------END CTOR / DTOR------------------------------------------

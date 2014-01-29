//
// Core.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:58:09 2014 guillaume marescaux
// Last update Wed Jan 29 12:52:11 2014 guillaume marescaux
//

#include		<string.h>
#include		"Core/Core.hh"
#include		"Crypto/Crypto.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Core::Core():
  _sockets(new std::map<eSocket, Socket *>),
  _socketsClient(new std::map<eSocket, ISocketClient *>),
  _infos(new ConnectionInfos),
  _player(NULL),
  _poll(new Poll),
  _proto(new Protocol(false))
{
  (*_sockets)[TCP] = new Socket;
  (*_sockets)[UDP] = new Socket;
  (*_socketsClient)[TCP] = NULL;
  (*_socketsClient)[UDP] = NULL;
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
  delete _proto;
}

//------------------------------------END CTOR / DTOR------------------------------------------

void				Core::readFromSocket(eSocket sock)
{
  static char			buff[SIZE_BUFFER];
  static std::string		tmp;
  CircularBufferManager		*manager = CircularBufferManager::getInstance();
  Trame				*tmpTrame;
  int				size;
  Crypto			*crypto = Crypto::getInstance();
  std::string			decrypted;

  if (_poll->isSet((*_socketsClient)[sock]->getSocket(), IPoll::READ))
    {
      memset(buff, 0, SIZE_BUFFER);
      tmp = "";
      // while (tmp.rfind(TRAMEEND) == std::string::npos)
      // 	{
	  size = (*_socketsClient)[sock]->readSocket(buff, SIZE_BUFFER);
	  if (size > 0)
	    tmp.append(buff, size);
      	  else
      	    {
	      std::cout << "ELSE" << std::endl;
      	      return;
      	    }
      	// }
      tmpTrame = new Trame();
      crypto->decryption(tmp, decrypted);
      Trame::toTrame(*tmpTrame, decrypted);
      manager->pushTrame(tmpTrame, CircularBufferManager::READ_BUFFER);
      std::cout << "TEEEEEEEEST" << std::endl;
      std::cout << decrypted << std::endl;
    }
}

//-------------------------------------BEGIN METHODS-------------------------------------------

void			Core::read(int const timeout, bool const setTimeout)
{
  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), IPoll::READ);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), IPoll::READ);
  _poll->setTimeout(timeout);
  _poll->runPoll(setTimeout);
  this->readFromSocket(Core::TCP);
  this->readFromSocket(Core::UDP);  
}

void			Core::init(void)
{
  Trame *trame = new Trame();
  Trame::readFile(*trame, CONNECT_FILE);
  _infos->ip = (*trame)["ip"].asString();
  _infos->port = (*trame)["port"].asInt();
  delete trame;

  (*_sockets)[TCP]->initialize("TCP");
  (*_sockets)[UDP]->initialize("UDP");
  (*_socketsClient)[TCP] = (*_sockets)[TCP]->connectToAddr(_infos->ip, _infos->port);
  (*_socketsClient)[UDP] = (*_sockets)[UDP]->connectToAddr(_infos->ip, _infos->port);
  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), IPoll::RDWRDC);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), IPoll::RDWR);
  this->read(0, false);
}

//--------------------------------------END METHODS--------------------------------------------

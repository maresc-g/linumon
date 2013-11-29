//
// Server.cpp for  in /home/ansel_l/Documents/Rtype/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 20:02:48 2013 laurent ansel
// Last update Fri Nov 29 15:48:15 2013 laurent ansel
//

#include			<list>
#include			<sstream>
#include			<signal.h>
#include			"Server/Server.hh"
#include			"CircularBufferManager/CircularBufferManager.hh"

bool				quit = false;

void				ctrl_c(int)
{
  quit = true;
#ifdef DEBUG_SERVER
  std::cout << "\b\bSignal : ctrl-c" << std::endl;
#endif
}

Server::Server(int const port):
  _clientId(1),
  _socket(new std::map<std::string, Socket *>),
  _poll(new Poll)
{
  this->_socket->insert(std::make_pair("TCP" , new Socket));
  this->debug("Initialize tcp socket ...");
  (*this->_socket)["TCP"]->initialize("TCP");
  this->debug("Done\nBind tcp socket ...");
  (*this->_socket)["TCP"]->bindSocket(port);
  this->debug("Done\nlisten ...");
  (*this->_socket)["TCP"]->listenSocket();
  this->debug("Done");
  this->_socket->insert(std::make_pair("UDP" , new Socket));
  this->debug("Initialize udp socket ...");
  (*this->_socket)["UDP"]->initialize("UDP");
  this->debug("Done\nBind udp socket ...");
  (*this->_socket)["UDP"]->bindSocket(port);
  this->debug("Done");
  (*this->_socket)["UDP"]->initAddr();
  CircularBufferManager::getInstance();
}

Server::~Server()
{
  if ((*this->_socket)["TCP"])
    {
      (*this->_socket)["TCP"]->destroy();
      delete (*this->_socket)["TCP"];
    }
  if ((*this->_socket)["UDP"])
    {
      (*this->_socket)["UDP"]->destroy();
      delete (*this->_socket)["UDP"];
    }
  delete _socket;
  delete _poll;
  CircularBufferManager::deleteInstance();
}

void				Server::debug(std::string const &str) const
{
#ifdef DEBUG_SERVER
  std::cout << str << std::endl;
#else
  (void)str;
#endif
}

void				Server::initializePoll() const
{
  this->_poll->pushFd((*this->_socket)["TCP"]->getSocket().getSocket(), IPoll::RDDC);
  this->_poll->pushFd((*this->_socket)["UDP"]->getSocket().getSocket(), IPoll::RDDC);
}

void				Server::runPoll() const
{
  this->debug("Run Poll ...");
  this->_poll->runPoll(false);
  this->debug("Done");
}

void				Server::run()
{
  signal(SIGINT, &ctrl_c);
  this->initializePoll();
  while (!quit)
    {
      this->runPoll();
    }
  this->debug("Shutdown Server ...");
  this->debug("GoobBye !");
}

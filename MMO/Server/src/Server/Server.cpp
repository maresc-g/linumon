//
// Server.cpp for  in /home/ansel_l/Documents/Rtype/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 20:02:48 2013 laurent ansel
// Last update Thu Jan 30 09:20:08 2014 laurent ansel
//

#include			<list>
#include			<sstream>
#include			<signal.h>
#include			<boost/function.hpp>
#include			<functional>
#include			"Server/Server.hh"
#include			"CircularBufferManager/CircularBufferManager.hh"
#include			"Error/Error.hpp"
#include			"Chat/Chat.hh"

bool				quit = false;

void				ctrl_c(int)
{
  quit = true;
#ifdef DEBUG_SERVER
  std::cout << "\b\bSignal : ctrl-c" << std::endl;
#endif
}

Server::Server(/*int const port*/):
  _socket(new std::map<std::string, Socket *>),
  _poll(new Poll),
  _actionServer(new std::map<FD, std::pair<bool, bool> >),
  _mutex(new Mutex),
  _codeBreaker(new CodeBreaker),
  _protocol(new Protocol(true))
{
}

Server::~Server()
{
  ClientManager::getInstance()->setQuit(true);
  ClientManager::getInstance()->join();
  Chat::getInstance()->setQuit(true);
  Chat::getInstance()->join();
  _codeBreaker->setQuit(true);
  _codeBreaker->join();
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
  this->_mutex->lock();
  delete this->_actionServer;
  CircularBufferManager::deleteInstance();
  ClientManager::deleteInstance();
  Chat::deleteInstance();
  delete _codeBreaker;
  Crypto::deleteInstance();
  delete _protocol;
  ObjectPoolManager::deleteInstance();
  this->_mutex->unlock();
  this->_mutex->destroy();
  delete this->_mutex;
}

void				Server::init(int const port)
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
  this->_mutex->init();
  Chat::getInstance();
  Crypto::getInstance();
  CircularBufferManager::getInstance();
  _codeBreaker->start();
  this->debug("Initialization protocol ...");

  this->debug("Done");
  ClientManager::getInstance()->setWriteFunction(&somethingWrite);
  this->debug("Starting ObjectPoolManager ...");
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  ObjectPoolManager::getInstance()->runObjectPool<Error>("error");
  this->debug("Done");
}

void				Server::debug(std::string const &str) const
{
#ifdef DEBUG_SERVER
  std::cout << str << std::endl;
#else
  (void)str;
#endif
}

bool				Server::addFuncProtocol(std::string const &key, std::function<bool (Trame *)> func)
{
  bool				ret;

  this->_mutex->lock();
  ret = this->_protocol->addFunc(key, func);
  this->_mutex->unlock();
  return (ret);
}

bool				Server::callProtocol(std::string const &key, unsigned int const id, void *param)
{
  bool				ret = false;

  this->_mutex->lock();
  ret = this->_protocol->operator()(key, id, param);
  ClientManager::getInstance()->newTrameToWrite(id, 1);
  this->_mutex->unlock();
  return (ret);
}

bool				Server::callProtocol(Trame *trame)
{
  this->_mutex->lock();
  this->_protocol->decodeTrame(trame);
  this->_mutex->unlock();
  return (true);
}


void				Server::detectWrite(FD const fd)
{
  this->_mutex->lock();
  if (this->_actionServer->find(fd) != this->_actionServer->end() && !(*this->_actionServer)[fd].second)
    {
      (*this->_actionServer)[fd].second = true;
      this->_poll->pushFd(fd, IPoll::RDWRDC);
   }
  this->_mutex->unlock();
}

void				somethingWrite(FD const fd)
{
  Server::getInstance()->detectWrite(fd);
}

void				Server::initializePoll() const
{
  this->_poll->pushFd((*this->_socket)["TCP"]->getSocket().getSocket(), IPoll::READ);
  this->_poll->pushFd((*this->_socket)["UDP"]->getSocket().getSocket(), IPoll::READ);
}

void				Server::runPoll() const
{
  // this->debug("Run Poll ...");
  this->_poll->setTimeout(30);
  this->_poll->runPoll(true);
  //this->debug("Done");
}

bool				Server::acceptNewClient()
{
   ISocketClient		*client;
   Header			*header = NULL;

   this->debug("NewClient ...");
   client = (*this->_socket)["TCP"]->acceptConnection();
   if (!ObjectPoolManager::getInstance()->setObject(header, "header"))
     return (false);
   header->setAll(client->getSocket(), "TCP");
   ClientManager::getInstance()->newClient(*header, client);
   this->_mutex->lock();
   (*this->_actionServer)[header->getIdClient()] = std::make_pair(false, false);
   this->_poll->pushFd(header->getIdClient(), IPoll::RDWRDC);
   std::cout << "CLIENT = " << header->getIdClient() << std::endl;
   this->_mutex->unlock();
   this->callProtocol("WELCOME", header->getIdClient(), NULL);
   delete header;
   this->debug("Done");
   return (true);
}

bool				Server::recvUdp()
{
  char                          tmp[SIZE_BUFFER] = "";
  std::string			decrypt;
  std::string			str;
  int				ret = (*this->_socket)["UDP"]->getSocket().readSocket(tmp, SIZE_BUFFER);
  Trame				*trame;

  this->_mutex->lock();
  if (ret > 0)
    {
      str.append(tmp, ret);
      //      decrypt.append(tmp, ret);
      // if (Crypto::getInstance()->decryption(decrypt, str))
      // 	{
	  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
	  Trame::toTrame(*trame, str);
	  if ((*trame)[CONTENT].isMember("INITIALIZE"))
	    {
	      ClientManager::getInstance()->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), &(*this->_socket)["UDP"]->getSocket(), "UDP");
	      this->_mutex->unlock();
	      this->callProtocol("CHECK", (*trame)[HEADER]["IDCLIENT"].asInt(), NULL);
	      this->_mutex->lock();
	    }
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::READ_BUFFER);
	// }
    }
  //  ClientManager::getInstance()->setInfoClient((*this->_socket)["UDP"]->getSocket().getSocket(), true, "UDP");
  this->_mutex->unlock();
  return (true);
}

bool				Server::disconnect()
{
  quit = true;
  return (true);
}

void				Server::actionServer()
{
  static struct	s_func<enum IPoll::ePoll, bool>		tab[] =
  {
    {IPoll::READ,		&Server::acceptNewClient},
    {IPoll::READ,		&Server::recvUdp},
    // {IPoll::DISCONNECT,		&Server::disconnect},
  };
  static unsigned int		size = sizeof(tab) / sizeof(*tab);

  for (unsigned int i = 0 ; i < size ; i += 2)
    {
      if (this->_poll->isSet((*this->_socket)["TCP"]->getSocket().getSocket(), tab[i]._type))
	(this->*tab[i].func)();
    }
  for (unsigned int i = 1 ; i < size ; ++i)
    {
      if (this->_poll->isSet((*this->_socket)["UDP"]->getSocket().getSocket(), tab[i]._type))
	(this->*tab[i].func)();
    }
}

bool				Server::readSomething(std::map<FD, std::pair<bool, bool> >::iterator &it)
{
  this->debug("read ...");
  this->_mutex->lock();
  ClientManager::getInstance()->setInfoClient(it->first, "TCP", true);
  this->_mutex->unlock();
  this->debug("Done");
  return (true);
}

bool				Server::writeSomething(std::map<FD, std::pair<bool, bool> >::iterator &it)
{
  this->debug("write ...");
  this->_mutex->lock();
  if (this->_actionServer->find(it->first) != this->_actionServer->end())
    {
      it->second.second = false;
      ClientManager::getInstance()->setInfoClient(it->first, "TCP", false);
      this->_poll->pushFd(it->first, IPoll::RDDC);
    }
  this->_mutex->unlock();
  this->debug("Done");
  return (true);
}

bool				Server::disconnectClient(std::map<FD, std::pair<bool, bool> >::iterator &it)
{
  this->debug("disconnect ...");
  this->_mutex->lock();
  ClientManager::getInstance()->setInfoClient(it->first);
  this->_poll->rmFd(it->first);
  it = this->_actionServer->erase(it);
  if (it != this->_actionServer->begin())
    --it;
  this->_mutex->unlock();
  this->debug("Done");
  return (true);
}

void				Server::actionClient()
{
  static struct s_func<enum IPoll::ePoll, bool, std::map<FD, std::pair<bool, bool> >::iterator &>	tab[] =
  {
    {IPoll::READ,		&Server::readSomething},
    {IPoll::WRITE,		&Server::writeSomething},
    {IPoll::DISCONNECT,		&Server::disconnectClient},

  };
  static unsigned int		size = sizeof(tab) / sizeof(*tab);

  for (unsigned int i = 0 ; i < size ; ++i)
    {
      this->_mutex->lock();
      for (auto it = this->_actionServer->begin() ; it != this->_actionServer->end() ; ++it)
	if (this->_poll->isSet((*it).first, tab[i]._type))
	  {
	    this->_mutex->unlock();
	    (this->*tab[i].func)(it);
	    if (this->_actionServer->empty())
	      {
		this->_mutex->lock();
		break;
	      }
	    this->_mutex->lock();
	  }
        this->_mutex->unlock();
    }
}

void				Server::run()
{
  signal(SIGINT, &ctrl_c);
  this->initializePoll();
  while (!quit)
    {
      this->runPoll();
      if (!quit)
	this->actionServer();
      if (!quit)
	this->actionClient();
    }
  this->debug("Shutdown Server ...");
  this->debug("GoobBye !");
}

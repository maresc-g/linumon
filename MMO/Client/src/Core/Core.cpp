//
// Core.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:58:09 2014 guillaume marescaux
// Last update Mon Feb  3 12:32:27 2014 guillaume marescaux
//

#include			<unistd.h>
#include			<string.h>
#include			<functional>
#include			"Core/Core.hh"
#include			"Crypto/Crypto.hh"

static void			*runThread(void *data)
{
  if (data)
    {
      Core			*core = reinterpret_cast<Core *>(data);

      core->run();
    }
  return (NULL);
}

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Core::Core(MutexVar<eState> *state):
  Thread(),
  _sockets(new std::map<eSocket, Socket *>),
  _socketsClient(new std::map<eSocket, ISocketClient *>),
  _infos(new ConnectionInfos),
  _player(NULL),
  _poll(new Poll),
  _proto(new Protocol(false)),
  _id(0),
  _initialized(new MutexVar<bool>(false)),
  _running(new MutexVar<bool>(true)),
  _state(state)
{
  std::function<bool (Trame *)> func;
  func = std::bind1st(std::mem_fun(&Core::welcome), this);
  _proto->addFunc("WELCOME", func);
  func = std::bind1st(std::mem_fun(&Core::check), this);
  _proto->addFunc("CHECK", func);

  (*_sockets)[TCP] = new Socket;
  (*_sockets)[UDP] = new Socket;
  (*_socketsClient)[TCP] = NULL;
  (*_socketsClient)[UDP] = NULL;
  this->create(&runThread, this);
  this->start();
}

Core::~Core()
{
  this->join();
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
  ObjectPoolManager::deleteInstance();
}

//------------------------------------END CTOR / DTOR------------------------------------------

//---------------------------------BEGIN PRIVATE METHODS---------------------------------------

void				Core::readFromSocket(eSocket sock)
{
  static char			buff[SIZE_BUFFER];
  static std::string		tmp;
  CircularBufferManager		*manager = CircularBufferManager::getInstance();
  Trame				*tmpTrame;
  int				size;
  // Crypto			*crypto = Crypto::getInstance();
  std::string			decrypted;

  if (_poll->isSet((*_socketsClient)[sock]->getSocket(), IPoll::READ))
    {
      memset(buff, 0, SIZE_BUFFER);
      tmp = "";
      // decrypted = "";
      // while (decrypted.rfind(TRAMEEND) == std::string::npos)
      while (tmp.rfind(TRAMEEND) == std::string::npos)
      	{
	  size = (*_socketsClient)[sock]->readSocket(buff, SIZE_BUFFER);
	  if (size > 0)
	    {
	      tmp.append(buff, size);
	      // crypto->decryption(tmp, decrypted);
	    }
      	  else
      	    {
      	      return;
      	    }
      	}
      // Trame::toTrame(*tmpTrame, decrypted);
      tmpTrame = new Trame;
      Trame::toTrame(*tmpTrame, tmp);
      manager->pushTrame(tmpTrame, CircularBufferManager::READ_BUFFER);
    }
}

void                            Core::writeToSocket(Trame const &trame, eSocket sock)
{
  static std::string            trameBuff;
  static char                   buff[SIZE_BUFFER];

  trameBuff = trame.toString();
  memset(buff, 0, SIZE_BUFFER);
  trameBuff.copy(buff, trameBuff.size());
  (*_socketsClient)[sock]->writeSocket(buff, trameBuff.size());
}
                                
bool				Core::welcome(Trame *trame)
{
  Header			*header;

  header = Header::deserialization(*trame);
  _id = header->getIdClient();
  (*_proto)("INITIALIZE", _id, NULL);
  return (true);
}

bool				Core::check(Trame *)
{
  *_initialized = true;
  return (true);
}

bool				Core::handlerError(Trame *)
{
  return (true);
}

bool				Core::map(Trame *trame)
{
  
}

//----------------------------------END PRIVATE METHODS----------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				Core::quit()
{
  *_running = false;
}

void                            Core::write()
{
  CircularBufferManager         *manager = CircularBufferManager::getInstance();
  Trame                         *tmp;

  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), Poll::WRITE);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), Poll::WRITE);
  tmp = manager->popTrame(_id, "TCP", CircularBufferManager::WRITE_BUFFER);
  if (!tmp)
    tmp = manager->popTrame(_id, "UDP", CircularBufferManager::WRITE_BUFFER);
  while (tmp)
    {
      _poll->runPoll(false);
      if ((*tmp)[HEADER]["PROTOCOLE"].asString() == "TCP")
        {
          if (_poll->isSet((*_socketsClient)[TCP]->getSocket(), Poll::WRITE))
            writeToSocket(*tmp, Core::TCP);
        }
      else if ((*tmp)[HEADER]["PROTOCOLE"].asString() == "UDP")
        {
          if (_poll->isSet((*_socketsClient)[UDP]->getSocket(), Poll::WRITE))
            writeToSocket(*tmp, Core::UDP);
        }
      delete tmp;
      tmp = manager->popTrame(_id, "TCP", CircularBufferManager::WRITE_BUFFER);
      if (!tmp)
        tmp = manager->popTrame(_id, "UDP", CircularBufferManager::WRITE_BUFFER);
    }
}

void				Core::read(int const timeout, bool const setTimeout)
{
  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), IPoll::READ);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), IPoll::READ);
  _poll->setTimeout(timeout);
  _poll->runPoll(setTimeout);
  this->readFromSocket(Core::TCP);
  this->readFromSocket(Core::UDP);  
}

void				Core::connection(Protocol::LoginInfos *infos)
{
  (*_proto)("CONNECTION", _id, infos);
}

void				Core::choosePlayer(int id)
{
  (*_proto)("CHOOSEPLAYER", _id, &id);
}

void				Core::init(void)
{
  Trame				*trame = new Trame();
  CircularBufferManager		*manager = CircularBufferManager::getInstance();

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
  while (!(trame = manager->popTrame(CircularBufferManager::READ_BUFFER)))
    this->read(0, false);
  _proto->decodeTrame(trame);
  this->write();
  while (!(trame = manager->popTrame(CircularBufferManager::READ_BUFFER)))
    this->read(0, false);
  _proto->decodeTrame(trame);
}

void				Core::run()
{
  while (**_running)
    {
      while (!**_initialized)
	usleep(100000);
      if (**_running)
	this->loop();
      usleep(1000);
    }
}

void				Core::loop()
{
  Trame				*trame = new Trame();
  CircularBufferManager		*manager = CircularBufferManager::getInstance();

  this->read(0, true);
  trame = manager->popTrame(CircularBufferManager::READ_BUFFER);
  if (trame)
    {
      _proto->decodeTrame(trame);
    }
  this->write();
}

//--------------------------------------END METHODS--------------------------------------------

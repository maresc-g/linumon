//
// Chat.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Jan 28 13:21:19 2014 laurent ansel
<<<<<<< HEAD
// Last update Wed Feb  5 16:01:30 2014 laurent ansel
=======
// Last update Wed Feb  5 16:33:48 2014 antoine maitre
>>>>>>> 443fe03e89ad7ef72e97cd6e9729b3986adfea8b
//

# include			"Chat/Chat.hh"
# include			"Server/Server.hh"
# include			"Map/Map.hh"

Chat::Chat():
  Thread(),
  _msg(new std::list<std::pair<bool, Trame *> >),
  _quit(false),
  _mutex(new Mutex)
{
  _mutex->init();
  _mutex->lock();

  Trame			*trame = NULL;

  for (int i = 0 ; i < DEFAULT_STORAGE_CHAT ; ++i)
    _msg->push_back(std::make_pair(false, trame));
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&Chat::newMsg), this);
  Server::getInstance()->addFuncProtocol("CHAT", func);

  _mutex->unlock();
  this->create(&runChat, this);
  this->start();
}

Chat::~Chat()
{
  _mutex->lock();
  for (auto it = _msg->begin() ; it != _msg->end() ; ++it)
    delete (*it).second;
  delete _msg;
  _mutex->unlock();
  _mutex->destroy();
  delete _mutex;
}

void				Chat::run()
{
  Header			*header = NULL;

  while (!header)
    ObjectPoolManager::getInstance()->setObject(header, "header");
  header->setProtocole("UDP");
  _mutex->lock();
  while (!_quit)
    {
      Trame			*trame = NULL;
      std::list<AEntity *>	list;
      Zone			*zone = NULL;

      for (auto it = this->_msg->begin() ; it != this->_msg->end() ; ++it)
	{
	  if ((*it).first)
	    {
	      (*it).first = false;
	      if ((zone = Map::getInstance()->getZone(static_cast<ZONE::eZone>((*trame)["CHAT"]["ZONE"].asInt()))))
		Server::getInstance()->callProtocol<Trame *, Zone *, bool>("SENDTOALLCLIENT", (*trame)[HEADER]["IDCLIENT"].asUInt(), (*it).second, zone, true);
	    }
	}
      _mutex->unlock();
      usleep(50000); //calculer le temps
      _mutex->lock();
    }
  _mutex->unlock();
}

void				Chat::setQuit(bool const quit)
{
  this->_mutex->lock();
  this->_quit = quit;
  this->_mutex->unlock();
}

bool				Chat::newMsg(Trame *trame)
{
  if (trame->isMember("CHAT"))
    {
      if ((*trame)["CHAT"].isMember("MESSAGE") && (*trame)["CHAT"].isMember("FACTION"))
	{
	  _mutex->lock();
	  auto it = this->_msg->begin();

	  for (it = this->_msg->begin() ; it != this->_msg->end() && (*it).first ; ++it);
	  if (it != this->_msg->end())
	    {
	      if (!(*it).second)
		ObjectPoolManager::getInstance()->setObject((*it).second, "trame");
	      if ((*it).second)
		{
		  (*it).first = true;
		  (*it).second->clear();
		  *(*it).second = *static_cast<Trame *>(&(*trame)["CHAT"]);
		}
	    }
	  else
	    {
	      Trame		*trame = NULL;

	      ObjectPoolManager::getInstance()->setObject(trame, "trame");
	      *trame = *static_cast<Trame *>(&(*trame)["CHAT"]);
	      this->_msg->push_back(std::make_pair(true, trame));
	    }
	  _mutex->unlock();
	}
      return (true);
    }
  return (false);
}

void				*runChat(void *data)
{
  if (data)
    {
      Chat		*chat = reinterpret_cast<Chat *>(data);

      chat->run();
    }
  return (NULL);
}

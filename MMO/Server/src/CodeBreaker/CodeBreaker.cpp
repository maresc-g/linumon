//
// CodeBreaker.cpp for  in /home/ansel_l/Documents/Pfa/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  1 14:52:17 2013 laurent ansel
// Last update Mon Feb 17 16:04:08 2014 laurent ansel
//

#include			"CodeBreaker/CodeBreaker.hh"
#include			"Server/Server.hh"

CodeBreaker::CodeBreaker():
  _list(new std::list<std::pair<Trame *, bool> >),
  _mutex(new Mutex()),
  _quit(false)
{
  _mutex->init();
  this->create(&runCodeBreaker, this);
}

CodeBreaker::~CodeBreaker()
{
  std::cout << "CodeBreaker DELETE " << std::flush;
  _mutex->lock();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if ((*it).first)
      {
	delete (*it).first;
	std::cout << "." << std::flush;
      }
  delete _list;
  std::cout << "." << std::flush;
  std::cout << "." << std::flush;
  _mutex->unlock();
  _mutex->destroy();
  std::cout << "." << std::flush;
  delete _mutex;
  std::cout << "." << std::flush;
  std::cout << std::endl << "Done" << std::endl;
}

void				CodeBreaker::getNewObject()
{
  Trame				*trame;

  this->_mutex->lock();
  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  if (trame)
    this->_list->push_back(std::make_pair(trame, false));
  this->_mutex->unlock();
}

bool				CodeBreaker::newCode(std::string const &str)
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_list->begin() ; it != this->_list->end() ; ++it)
    {
      if (!(*it).second)
	{
	  (*it).first->clear();
	  Trame::toTrame(*(*it).first, str);
	  (*it).second = true;
	  set = true;
	}
    }
  this->_mutex->unlock();
  if (!set)
    {
      this->getNewObject();
      this->_mutex->lock();
      Trame::toTrame(*this->_list->back().first, str);
      this->_list->back().second = true;
      this->_mutex->unlock();
      set = true;
    }
  return (set);
}

bool				CodeBreaker::newCode(Trame *trame)
{
  bool				set = false;

  if (trame)
    {
      this->_mutex->lock();
      for (auto it = this->_list->begin() ; it != this->_list->end() ; ++it)
	{
	  if (!(*it).second)
	    {
	      (*it).first->clear();
	      *(*it).first = *trame;
	      (*it).second = true;
	      set = true;
	    }
	}
      this->_mutex->unlock();
      if (!set)
	{
	  this->getNewObject();
	  this->_mutex->lock();
	  *this->_list->back().first = trame;
	  this->_list->back().second = true;
	  this->_mutex->unlock();
	  set = true;
	}
    }
  return (set);

}

void				CodeBreaker::execCode()
{
  this->_mutex->lock();
  for (auto it = this->_list->begin() ; it != this->_list->end() ; ++it)
    if ((*it).second)
      {
	std::cout << "CODE BREAKER" << std::endl;
	Server::getInstance()->callProtocol((*it).first);
	it->second = false;
      }
  this->_mutex->unlock();
}

void				CodeBreaker::run()
{
  Trame				*trame;

  this->_mutex->lock();
  while (!_quit)
    {
      this->_mutex->unlock();
      trame = CircularBufferManager::getInstance()->popTrame(CircularBufferManager::READ_BUFFER);
      if (trame)
	std::cout << "NOT NULL" << std::endl;
      this->newCode(trame);
      delete trame;
      this->execCode();
      usleep(50000);
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

void				CodeBreaker::setQuit(bool const quit)
{
  this->_quit = quit;
}

void				*runCodeBreaker(void *data)
{
  if (data)
    {
      CodeBreaker			*code = reinterpret_cast<CodeBreaker *>(data);

      if (code)
	code->run();
    }
  return (NULL);
}

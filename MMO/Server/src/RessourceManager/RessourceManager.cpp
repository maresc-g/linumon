//
// RessourceManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Feb 17 14:29:34 2014 laurent ansel
// Last update Tue Feb 18 13:28:32 2014 laurent ansel
//

#include			<ctime>
#include			<ratio>
#include			<chrono>
#include			<boost/chrono.hpp>
#include			"RessourceManager/RessourceManager.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"Map/Map.hh"

RessourceManager::RessourceManager():
  Thread(),
  _ressources(new std::map<std::string, std::list<Ressource *> *>),
  _action(new std::list<std::pair<bool, RessourcePop *> >),
  _mutex(new Mutex),
  _quit(false)
{
  _mutex->init();
  _mutex->lock();
  for (auto i = 0 ; i < DEFAULT_ACTION ; ++i)
    _action->push_back(std::make_pair(false, new RessourcePop));
  _mutex->unlock();
  this->create(&runRessourceManager, this);
  this->start();
  this->init();
}

RessourceManager::~RessourceManager()
{
  _mutex->lock();
  for (auto it = _ressources->begin() ; it != _ressources->end() ; ++it)
    {
      for (auto im = it->second->begin() ; im != it->second->end() ; ++im)
	delete *im;
      delete it->second;
    }
  delete _ressources;
  for (auto it = _action->begin() ; it != _action->end() ; ++it)
    delete it->second;
  delete _action;
  _mutex->unlock();
  _mutex->destroy();
  delete _mutex;
}

void				RessourceManager::init()
{
  Trame				*file = NULL;
  Ressource			*res = NULL;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  this->_mutex->lock();
  if (JsonFile::readFile(*file, PATH_RESSOURCES_FILE))
    {
      auto			members = (*file).getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  auto			zoneMembers = (*file)[*it].getMemberNames();

	  (*_ressources)[*it] = new std::list<Ressource *>;
	  for (auto im = zoneMembers.begin() ; im != zoneMembers.end() ; ++im)
	    {
	      res = Ressource::deserialization((*file)((*file)[*it][*im]));
	      if (res)
		{
		  (*_ressources)[*it]->push_back(res);
		  Map::getInstance()->addEntity(*it, res);
		}
	    }
	}
    }
  this->_mutex->unlock();
}

void				RessourceManager::newTime(double const microsecond)
{
  double			time = 0;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    if (it->first)
      {
	it->second->time -= microsecond;
	if (it->second->time <= 0)
	  {
	    this->_mutex->unlock();
	    time += this->setRessource(it);
	    this->_mutex->lock();
	  }
      }
  this->_mutex->unlock();
  if (time > 0)
    this->newTime(time);
}

double				RessourceManager::setRessource(std::list<std::pair<bool, RessourcePop *> >::iterator &it)
{
  std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
  bool				set = false;

  this->_mutex->lock();
  auto			ir = this->_ressources->begin();

  if ((ir = this->_ressources->find(it->second->zone)) != this->_ressources->end())
    {
      for (auto res = ir->second->begin() ; res != ir->second->end() && !set; ++res)
	{
	  if (*res && (*res)->getX() == it->second->coord.getX() && (*res)->getY() == it->second->coord.getY())
	    {
	      it->second->ressource = *res;
	      it->first = true;
	      set = true;
	    }
	}
    }
  this->_mutex->unlock();
  std::chrono::system_clock::time_point	end = std::chrono::system_clock::now();

  std::chrono::duration<double, std::micro> time = std::chrono::duration_cast<std::chrono::duration<double, std::micro> >(end - start);
  return (time.count());
}

void				RessourceManager::run()
{
  this->_mutex->lock();
  while (!_quit)
    {
      this->_mutex->unlock();
      usleep(30000);
      this->newTime(30000);
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

void				RessourceManager::setQuit(bool const quit)
{
  _quit = quit;
}

void				RessourceManager::needRessource(Ressource::RessourceCoordinate const &coord, std::string const &zone)
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = _action->begin() ; it != _action->end() && !set ; ++it)
    {
      if (!it->first && it->second)
	{
	  it->second->time = DEFAULT_TIME;
	  it->second->zone = zone;
	  it->second->coord = coord;
	  set = true;
	}
    }
  this->_mutex->unlock();
}

void				*runRessourceManager(void *data)
{
  if (data)
    {
      RessourceManager		*tmp = reinterpret_cast<RessourceManager *>(data);

      tmp->run();
    }
  return (NULL);
}

/*
**
**	RESOURCEPOP
**
*/

RessourcePop::RessourcePop():
  time(0),
  zone(""),
  coord(0, 0),
  ressource(NULL)
{

}

RessourcePop::~RessourcePop()
{
}

void				RessourcePop::clear()
{
  this->time = 0;
  this->zone = "";
  this->coord.setX(0);
  this->coord.setY(0);
  this->ressource = NULL;
}
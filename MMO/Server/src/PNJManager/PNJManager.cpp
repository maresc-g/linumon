//
// PNJManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 14:02:30 2014 laurent ansel
// Last update Tue Feb 25 14:29:24 2014 laurent ansel
//

#include			"PNJManager/PNJManager.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"Map/Map.hh"

PNJManager::PNJManager() :
  _pnjs(new std::map<std::string, std::list<PNJ *> *>),
  _mutex(new Mutex)
{
  _mutex->init();
  this->init();
}

PNJManager::~PNJManager()
{
  _mutex->lock();
  Trame				*trame = NULL;
  unsigned int			nb = 0;
  std::ostringstream		str;

  ObjectPoolManager::getInstance()->setObject(trame, "trame");
  for (auto it = _pnjs->begin() ; it != _pnjs->end() ; ++it)
    {
      nb = 0;
      for (auto im = it->second->begin() ; im != it->second->end() ; ++im)
	{
	  str.str("");
	  str << "PNJ" << nb;
	  (*im)->serialization((*trame)((*trame)[it->first][str.str()]));
	  delete *im;
	  nb++;
	}
      delete it->second;
    }
  delete _pnjs;
  if (nb)
    trame->writeInFile(PATH_PNJS_FILE);
  _mutex->unlock();
  _mutex->destroy();
  delete _mutex;
}

void				PNJManager::init()
{
  Trame				*file = NULL;
  PNJ				*pnj = NULL;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  this->_mutex->lock();
  if (JsonFile::readFile(*file, PATH_PNJS_FILE))
    {
      auto			members = (*file).getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  auto			zoneMembers = (*file)[*it].getMemberNames();

	  (*_pnjs)[*it] = new std::list<PNJ *>;
	  for (auto im = zoneMembers.begin() ; im != zoneMembers.end() ; ++im)
	    {
	      pnj = PNJ::deserialization((*file)((*file)[*it][*im]), false);
	      if (pnj)
		{
		  (*_pnjs)[*it]->push_back(pnj);
		  Map::getInstance()->addEntity(*it, pnj);
		}
	    }
	}
    }
  this->_mutex->unlock();
}

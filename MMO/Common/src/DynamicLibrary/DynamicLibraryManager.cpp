//
// DynamicLibraryManager.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 19:51:02 2013 alexis mestag
// Last update Sun Nov 24 22:51:26 2013 alexis mestag
//

#include			"DynamicLibrary/DynamicLibraryManager.hh"
#include			"DynamicLibrary/DynamicLibrary.hh"

DynamicLibraryManager::DynamicLibraryManager() :
  Singleton(), _updater(new DynamicLibraryUpdater), _libraries(new GameLibraries), _mtx(new Mutex)
{
  this->_mtx->initialize();
  this->_updater->startUpdate();
}

DynamicLibraryManager::DynamicLibraryManager(DynamicLibraryManager const &rhs) :
  Singleton(), _libraries(new GameLibraries), _mtx(new Mutex)
{
  this->_mtx->initialize();
  *this = rhs;
}

DynamicLibraryManager::~DynamicLibraryManager()
{
  this->_updater->stopUpdate();
  this->_updater->waitThread();
  delete _updater;
  delete _libraries;
  _mtx->destroy();
  delete _mtx;
}

DynamicLibraryManager		&DynamicLibraryManager::operator=(DynamicLibraryManager const &rhs)
{
  if (this != &rhs)
    {
    }
  return (*this);
}

GameLibraries			&DynamicLibraryManager::getGameLibrariesCopy() const
{
  GameLibraries			*ret;

  _mtx->enter();
  ret = &_libraries->getDeepCopy();
  _mtx->leave();
  return (*ret);
}

void				DynamicLibraryManager::setLibrary(IDynamicLibrary &lib, bool const lock)
{
  if (lock)
    _mtx->enter();
  _libraries->setLibrary(lib);
  if (lock)
    _mtx->leave();
}

void				DynamicLibraryManager::resetLibraries(std::list<FileSystem::Entry *> const *entries)
{
  IDynamicLibrary		*lib;

  _mtx->enter();
  _libraries->clear();
  for (auto it = entries->cbegin() ; it != entries->cend() ; ++it)
    {
      if ((*it)->getType() == FileSystem::FILE
  	  /* && filename matches pattern ? */)
  	{
  	  lib = new DynamicLibrary((*it)->getPath());
  	  this->setLibrary(*lib, false);
  	  std::cout << "\t" << lib->getPath() << std::endl;
  	}
    }
  _mtx->leave();
}

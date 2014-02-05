//
// DynamicLibraryUpdater.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 20:05:50 2013 alexis mestag
// Last update Sun Nov 24 22:48:01 2013 alexis mestag
//

#ifndef				_WIN32
#include			<unistd.h>
#endif
#include			<iostream>
#include			"DynamicLibrary/DynamicLibraryManager.hh"
#include			"DynamicLibrary/DynamicLibrary.hh"

static void			*run(void *data)
{
  DynamicLibraryUpdater		*dlu;
  bool				inotifyRet;

  dlu = reinterpret_cast<DynamicLibraryUpdater *>(data);
  do
    {
      std::cout << "Libraries directory was changed !" << std::endl;
      dlu->updateLibraries();
      inotifyRet = dlu->getInotify().waitEvent(dlu->getDirectory().getPath());
    } while (dlu->getCanUpdate() && inotifyRet);
  if (!inotifyRet)
    std::cerr << "Something went wrong while monitoring Libraries directory" << std::endl;
  return (NULL);
}

DynamicLibraryUpdater::DynamicLibraryUpdater(std::string const &path) :
  Thread(), _directory(new FileSystem::Directory(path)), _inotify(new Inotify),
  _mtx(new Mutex), _canUpdate(false)
{
  _mtx->initialize();
}

DynamicLibraryUpdater::~DynamicLibraryUpdater()
{
  delete _directory;
  _inotify->destroyInotify();
  delete _inotify;
  _mtx->destroy();
  delete _mtx;
}

void				DynamicLibraryUpdater::startUpdate()
{
  _inotify->initInotify();
  _inotify->addWatch(_directory->getPath(), IInotify::ALL_EVENT);
  this->setCanUpdate(true);
  this->createThread(&run, this);
  this->start();
}

void				DynamicLibraryUpdater::stopUpdate()
{
  this->setCanUpdate(false);
  _inotify->rmWatch(_directory->getPath());
}

void				DynamicLibraryUpdater::updateLibraries()
{
  DynamicLibraryManager		*dlm = DynamicLibraryManager::getInstance();
  std::list<FileSystem::Entry *> const	*entries;

  _directory->updateEntries();
  entries = &_directory->getEntries();
  dlm->resetLibraries(entries);
  // for (auto it = entries->cbegin() ; it != entries->cend() ; ++it)
  //   {
  //     if ((*it)->getType() == FileSystem::FILE
  // 	  /* && filename matches pattern ? */)
  // 	{
  // 	  lib = new DynamicLibrary((*it)->getPath());
  // 	  dlm->setLibrary(*lib);
  // 	  std::cout << "\t" << lib->getPath() << std::endl;
  // 	}
  //   }
}

FileSystem::Directory const	&DynamicLibraryUpdater::getDirectory() const
{
  return (*_directory);
}

Inotify				&DynamicLibraryUpdater::getInotify()
{
  return (*_inotify);
}

void				DynamicLibraryUpdater::setCanUpdate(bool const canUpdate)
{
  _mtx->enter();
  _canUpdate = canUpdate;
  _mtx->leave();
}

bool				DynamicLibraryUpdater::getCanUpdate() const
{
  bool				ret;

  _mtx->enter();
  ret = _canUpdate;
  _mtx->leave();
  return (ret);
}

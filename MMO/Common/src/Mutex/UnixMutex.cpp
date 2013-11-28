//
// UnixMutex.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 13:04:52 2013 laurent ansel
// Last update Tue Nov 26 00:40:36 2013 alexis mestag
//

#include		<iostream>
#include		"Mutex/UnixMutex.hh"

UnixMutex::UnixMutex():
  AMutex()
{

}

UnixMutex::~UnixMutex()
{

}

bool			UnixMutex::init()
{
  bool			ret = true;

  if (!this->isInit())
    {
      if (pthread_mutex_init(&this->_mutex, NULL)) {
	std::cerr << MUTEX_INIT_ERROR << std::endl;
	ret = false;
      }
      else
	this->setIsInit();
    }
  return (ret);
}

bool			UnixMutex::destroy()
{
  bool			ret = true;

  if (!this->isInit() || pthread_mutex_destroy(&this->_mutex)) {
    std::cerr << MUTEX_DESTROY_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool			UnixMutex::lock()
{
  bool			ret = true;

  if (!this->isInit() || pthread_mutex_lock(&this->_mutex)) {
    std::cerr << MUTEX_LOCK_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool			UnixMutex::tryLock()
{
  bool			ret = true;

  if (!this->isInit() || pthread_mutex_trylock(&this->_mutex)) {
    ret = false;
  }
  return (ret);
}

bool			UnixMutex::unlock()
{
  bool			ret = true;

  if (!this->isInit() || pthread_mutex_unlock(&this->_mutex)) {
    std::cerr << MUTEX_UNLOCK_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

pthread_mutex_t		*UnixMutex::getMutex()
{
  return (&this->_mutex);
}

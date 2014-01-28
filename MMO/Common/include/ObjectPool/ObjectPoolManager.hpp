//
// ObjectPoolManager.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  8 20:53:36 2013 laurent ansel
// Last update Fri Jan 24 16:40:53 2014 laurent ansel
//

#ifndef 			__OBJECTPOOLMANAGER_HPP__
# define 			__OBJECTPOOLMANAGER_HPP__

#include			<map>
#include			"ObjectPool/ObjectPool.hpp"
#include			"Utility/Singleton.hpp"

#define	LIMIT_COPY		100

class				ObjectPoolManager : public Singleton<ObjectPoolManager>
{
  friend class			Singleton<ObjectPoolManager>;
private:
  std::map<std::string, IObjectPool *>	*_map;
  Mutex				*_mutex;
  ObjectPoolManager():
    _map(new std::map<std::string, IObjectPool *>),
    _mutex(new Mutex)
  {
    _mutex->init();
  }
  virtual ~ObjectPoolManager()
  {
    _mutex->lock();
    for (auto it = _map->begin() ; it != _map->end() ; ++it)
      {
	it->second->setQuit(true);
	it->second->waitExit();
	delete it->second;
      }
    delete _map;
    _mutex->unlock();
    _mutex->destroy();
    delete _mutex;
  }
public:
  template<typename T>
  bool				runObjectPool(std::string const &key)
  {
    _mutex->lock();
    if ((_map->find(key)) == _map->end())
      {
	(*_map)[key] = new ObjectPool<T>;
	(*_map)[key]->startObjectPool();
	_mutex->unlock();
	return (true);
      }
    _mutex->unlock();
    return (false);
  }

  void				*getObject(std::string const &key)
  {
    std::map<std::string, IObjectPool *>::iterator	it;

    _mutex->lock();
    if ((it = _map->find(key)) != _map->end())
      {
	_mutex->unlock();
	return (it->second->getObject());
      }
    _mutex->unlock();
    return (NULL);
  }

  template<typename T>
  bool				setObject(T *&object, std::string const &key)
  {
    unsigned int		i;

    object = NULL;
    for (i = 0 ; i < LIMIT_COPY && !object ; ++i)
      {
	object = reinterpret_cast<T *>(getObject(key));
	if (!object)
	  usleep(1000);
      }
    if (i < LIMIT_COPY)
      return (true);
    return (false);
  }
};

#endif

//
// ObjectPool.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  1 19:08:45 2013 laurent ansel
// Last update Thu Jan 30 11:09:47 2014 laurent ansel
//

#ifndef 			__OBJECTPOOL_HPP__
# define 			__OBJECTPOOL_HPP__

#ifdef	_WIN32
#include			<windows.h>
#else
#include			<unistd.h>
#endif
#include			<typeinfo>
#include			"ObjectPool/IObjectPool.hh"
#include			"Mutex/Mutex.hpp"
#include			"Thread/Thread.hpp"

#define	DEFAULT_CREATE		500

template<typename>
void				*runObjectPoolThread(void *data);

template<typename T>
class				ObjectPool : public IObjectPool, public Thread
{
private:
  std::list<T *>		*_list;
  Mutex				*_mutex;
  bool				_quit;
  unsigned int			_nb;
public:
  ObjectPool(unsigned int const nb = DEFAULT_CREATE):
    _list(new std::list<T *>),
    _mutex(new Mutex()),
    _quit(false),
    _nb(nb)
  {
    _mutex->init();
    this->create(&runObjectPoolThread<T>, this);
  }

  virtual ~ObjectPool()
  {
    _mutex->lock();
    for (auto it = _list->begin() ; it != _list->end() ; ++it)
      delete *it;
    delete _list;
    _mutex->unlock();
    _mutex->destroy();
    delete _mutex;
  }

  virtual void			run()
  {
    unsigned int		time;

    this->_mutex->lock();
    while (!_quit)
      {
	this->_mutex->unlock();
	this->_mutex->lock();
	if (_list && _list->size() >= _nb / 2)
	  time = 600;
	else
	  time = 1;
	_list->push_back(new T());
	//	std::cout << "ptr {" << _list->back() << "}" << std::endl;
	this->_mutex->unlock();
#ifdef	_WIN32
	Sleep(time);
#else
	usleep(time * 1000);
#endif
	this->_mutex->lock();
      }
    this->_mutex->unlock();
  }

  virtual void			*getObject()
  {
    T				*tmp;

    this->_mutex->lock();
    tmp = this->_list->front();
    this->_list->pop_front();
    this->_mutex->unlock();
    return (tmp);
  }

  virtual void			setQuit(bool const quit)
  {
    this->_mutex->lock();
    this->_quit = quit;
    this->_mutex->unlock();
  }

  virtual void			startObjectPool()
  {
    this->start();
  }

  virtual bool			waitExit()
  {
    return (this->join());
  }
};

template<typename U>
void				*runObjectPoolThread(void *data)
{
  if (data)
    {
      ObjectPool<U>	*obj = reinterpret_cast<ObjectPool<U> *>(data);

      obj->run();
    }
  return (NULL);
}

#endif

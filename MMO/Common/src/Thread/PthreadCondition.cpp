//
// PthreadCondition.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 14:19:41 2013 laurent ansel
// Last update Tue Nov 26 00:58:26 2013 alexis mestag
//

#include			<iostream>
#include			"Thread/PthreadCondition.hh"

PthreadCondition::PthreadCondition():
  _mutex(new UnixMutex), _isInit(false)
{

}

PthreadCondition::~PthreadCondition()
{
  delete this->_mutex;
}

bool				PthreadCondition::init()
{
  bool				ret = true;

  if (!this->_mutex->init() || pthread_cond_init(&this->_cond, NULL)) {
    std::cerr << PTHREADCOND_INIT_ERROR << std::endl;
    ret = false;
  }
  else
    this->setIsInit(true);
  return (ret);
}

bool				PthreadCondition::destroy()
{
  bool				ret = false;

  if (this->isInit())
    {
      if (this->_mutex->destroy() && !pthread_cond_destroy(&this->_cond))
	ret = true;
    }
  if (!ret)
    std::cerr << PTHREADCOND_DESTROY_ERROR << std::endl;
  return (ret);
}

bool				PthreadCondition::signal()
{
  bool				ret = true;

  if (pthread_cond_signal(&this->_cond)) {
    std::cerr << PTHREADCOND_SIGNAL_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool				PthreadCondition::broadcast()
{
  bool				ret = true;

  if (pthread_cond_broadcast(&this->_cond)) {
    std::cerr << PTHREADCOND_BROADCAST_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool				PthreadCondition::wait()
{
  bool				ret = true;

  if (pthread_cond_wait(&this->_cond, this->_mutex->getMutex())) {
    std::cerr << PTHREADCOND_WAIT_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool				PthreadCondition::isInit() const
{
  return (this->_isInit);
}

void				PthreadCondition::setIsInit(bool const isInit)
{
  this->_isInit = isInit;
}

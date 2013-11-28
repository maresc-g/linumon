//
// UnixThread.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 13:25:46 2013 laurent ansel
// Last update Tue Nov 26 01:00:06 2013 alexis mestag
//

#include		<iostream>
#include		"Thread/UnixThread.hh"

UnixThread::UnixThread():
  _cond(new PthreadCondition), _func(NULL), _canStart(false)
{

}

UnixThread::~UnixThread()
{
  this->_cond->destroy();
  delete this->_cond;
}

bool			UnixThread::canStart() const
{
  return (this->_canStart);
}

void			UnixThread::setCanStart(bool const canStart)
{
  this->_canStart = canStart;
}

void			*UnixThread::trampoline(void *data)
{
  UnixThread		*thread = reinterpret_cast<UnixThread *>(data);

  if (thread->getCond())
    {
      while (!thread->canStart())
	thread->getCond()->wait();
      return (thread->getFunc()(thread->getData()));
    }
  return (NULL);
}

bool			UnixThread::create(void *(*func)(void *), void *data)
{
  bool			ret = true;

  this->setFunc(func);
  this->setData(data);
  if (!this->_cond->init() ||
      pthread_create(&this->_thread, NULL, &UnixThread::trampoline, this)) {
    std::cerr << THREAD_CREATE_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool			UnixThread::start()
{
  bool			ret = true;

  this->setCanStart();
  if (!this->_cond->signal()) {
    std::cerr << THREAD_START_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool			UnixThread::exit()
{
  pthread_exit(&this->_thread);
  return (true);
}

bool			UnixThread::cancel()
{
  bool			ret = true;

  if (pthread_cancel(this->_thread)) {
    std::cerr << THREAD_CANCEL_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

bool			UnixThread::join()
{
  bool			ret = true;

  if (pthread_join(this->_thread, NULL)) {
    std::cerr << THREAD_JOIN_ERROR << std::endl;
    ret = false;
  }
  return (ret);
}

PthreadCondition	*UnixThread::getCond()
{
  return (this->_cond);
}

void			UnixThread::setFunc(void *(*func)(void *))
{
  this->_func = func;
}

CallBack		UnixThread::getFunc()
{
  return (this->_func);
}

void			UnixThread::setData(void *data)
{
  this->_data = data;
}

void			*UnixThread::getData()
{
  return (this->_data);
}

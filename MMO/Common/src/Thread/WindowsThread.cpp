//
// WindowsThread.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:54:47 2013 laurent ansel
// Last update Tue Nov 12 20:28:33 2013 alexis mestag
//

#ifdef			_WIN32

#include		<exception>
#include		"Thread/WindowsThread.hh"

WindowsThread::WindowsThread():
  _thread(NULL)
{

}

WindowsThread::~WindowsThread()
{

}

int			WindowsThread::start()
{
  if (!this->_thread)
    return (1);
  ResumeThread(this->_thread);
  return (0);
}

int			WindowsThread::createThread(void *(*func)(void *), void *data)
{
  if ((this->_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, data, CREATE_SUSPENDED, NULL)) == NULL)
    {
      std::cerr << "error" << std::endl;
      return (1);
    }
  return (0);
}

void			WindowsThread::destroyThread()
{
  if (this->_thread)
    CloseHandle(this->_thread);
}

int			WindowsThread::cancelThread()
{
  throw std::exception();
}

int			WindowsThread::waitThread()
{
  if (WaitForSingleObject(this->_thread, INFINITE) == WAIT_FAILED)
    return (1);
  return (0);
}

#endif

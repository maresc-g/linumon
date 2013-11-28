//
// WindowsThread.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:54:47 2013 laurent ansel
// Last update Tue Nov 12 20:28:33 2013 alexis mestag
//

#include		<iostream>
#include		<exception>
#include		"Thread/WindowsThread.hh"

WindowsThread::WindowsThread():
  _thread(NULL)
{

}

WindowsThread::~WindowsThread()
{

}

bool			WindowsThread::start()
{
	bool		ret = true;

  if (ResumeThread(this->_thread) == -1) {
	  std::cerr << THREAD_START_ERROR << std::endl;
	  ret = false;
  }
  return (ret);
}

bool			WindowsThread::create(void *(*func)(void *), void *data)
{
	bool		ret = true;

	if ((this->_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, data, CREATE_SUSPENDED, NULL)) == NULL)
    {
      std::cerr << THREAD_CREATE_ERROR << std::endl;
	  ret = false;
    }
	return (ret);
}

bool			WindowsThread::exit()
{
	bool		ret = true;

    if (!CloseHandle(this->_thread)) {
		std::cerr << THREAD_EXIT_ERROR << std::endl;
		ret = false;
	}
	return (ret);
}

bool			WindowsThread::cancel()
{
  throw std::exception();
}

bool			WindowsThread::join()
{
	bool		ret = true;

	if (WaitForSingleObject(this->_thread, INFINITE) == WAIT_FAILED) {
	std::cerr << THREAD_JOIN_ERROR << std::endl;
	ret = false;
	}
	return (ret);
}
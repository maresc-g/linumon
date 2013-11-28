//
// WindowsThread.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:53:21 2013 laurent ansel
// Last update Tue Nov 12 20:24:44 2013 alexis mestag
//

#ifndef 			__WINDOWSTHREAD_HH__
# define 			__WINDOWSTHREAD_HH__

#ifdef				_WIN32

#define _WINSOCKAPI_
#include			<Windows.h>
#include			"Thread/IThread.hh"

class				WindowsThread : public IThread
{
private:
  HANDLE			_thread;
public:
  WindowsThread();
  virtual ~WindowsThread();
  virtual int			start();
  virtual int			createThread(void *(*func)(void*), void *);
  virtual void			destroyThread();
  virtual int			cancelThread();
  virtual int			waitThread();
};

#endif

#endif

//
// WindowsMutex.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:51:50 2013 laurent ansel
// Last update Mon Nov 25 22:03:08 2013 alexis mestag
//

#ifndef 			__WINDOWSMUTEX_HH__
# define 			__WINDOWSMUTEX_HH__

# define			_WINSOCKAPI_ 
# include			<Windows.h>
# include			"Mutex/AMutex.hh"

class				WindowsMutex : public AMutex
{
private:
  CRITICAL_SECTION		_section;

public:
  WindowsMutex();
  virtual ~WindowsMutex();
  virtual bool			init();
  virtual bool			destroy();
  virtual bool			lock();
  virtual bool			tryLock();
  virtual bool			unlock();
};

#endif


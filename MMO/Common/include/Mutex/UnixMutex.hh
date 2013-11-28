//
// UnixMutex.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 13:00:53 2013 laurent ansel
// Last update Tue Nov 26 00:39:32 2013 alexis mestag
//

#ifndef 			__UNIXMUTEX_HH__
# define 			__UNIXMUTEX_HH__

# include			<pthread.h>
# include			"Mutex/AMutex.hh"

class				UnixMutex : public AMutex
{
private:
  pthread_mutex_t		_mutex;

public:
  UnixMutex();
  virtual ~UnixMutex();
  virtual bool			init();
  virtual bool			destroy();
  virtual bool			lock();
  virtual bool			tryLock();
  virtual bool			unlock();

  pthread_mutex_t		*getMutex();
};

#endif

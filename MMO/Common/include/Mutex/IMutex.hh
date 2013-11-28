//
// IMutex.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:50:57 2013 laurent ansel
// Last update Mon Nov 25 22:00:00 2013 alexis mestag
//

#ifndef 			__IMUTEX_HH__
# define 			__IMUTEX_HH__

# define MUTEX_INIT_ERROR	"Cannot initialize mutex"
# define MUTEX_DESTROY_ERROR	"Cannot destroy mutex"
# define MUTEX_LOCK_ERROR	"Cannot lock mutex"
# define MUTEX_UNLOCK_ERROR	"Cannot unlock mutex"

class				IMutex
{
public:
  virtual ~IMutex() {}
  virtual bool			init() = 0;
  virtual bool			destroy() = 0;
  virtual bool			lock() = 0;
  virtual bool			tryLock() = 0;
  virtual bool			unlock() = 0;
};

#endif

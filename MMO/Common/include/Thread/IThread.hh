//
// IThread.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 12:53:00 2013 laurent ansel
// Last update Tue Nov 26 00:35:34 2013 alexis mestag
//

#ifndef 			__ITHREAD_HH__
# define 			__ITHREAD_HH__

# define THREAD_CREATE_ERROR	"Cannot create thread"
# define THREAD_START_ERROR	"Cannot start thread"
# define THREAD_EXIT_ERROR	"Cannot exit thread"
# define THREAD_CANCEL_ERROR	"Cannot cancel thread"
# define THREAD_JOIN_ERROR	"Cannot join thread"

class				IThread
{
public:
  virtual ~IThread() {}
  virtual bool			create(void *(*func)(void *), void *) = 0;
  virtual bool			start() = 0;
  virtual bool			exit() = 0;
  virtual bool			cancel() = 0;
  virtual bool			join() = 0;
};

#endif

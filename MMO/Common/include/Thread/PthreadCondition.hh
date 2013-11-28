//
// PthreadCondition.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 14:15:23 2013 laurent ansel
// Last update Tue Nov 26 00:36:15 2013 alexis mestag
//

#ifndef 			__PTHREADCONDITION_HH__
# define 			__PTHREADCONDITION_HH__

# include			<pthread.h>
# include			"Mutex/UnixMutex.hh"

# define PTHREADCOND_INIT_ERROR		"Cannot initialize pthread_cond"
# define PTHREADCOND_DESTROY_ERROR	"Cannot destroy pthread_cond"
# define PTHREADCOND_SIGNAL_ERROR	"Cannot send signal to thread [pthread_cond_signal()]"
# define PTHREADCOND_BROADCAST_ERROR	"Cannot broadcast threads [pthread_cond_broadcast()]"
# define PTHREADCOND_WAIT_ERROR		"Cannot wait in pthread_cond"

class				PthreadCondition
{
private:
  UnixMutex			*_mutex;
  bool				_isInit;
  pthread_cond_t		_cond;

  bool				isInit() const;
  void				setIsInit(bool const isInit = true);

public:
  PthreadCondition();
  virtual ~PthreadCondition();
  bool				init();
  bool				destroy();
  bool				signal();
  bool				broadcast();
  bool				wait();
};

#endif

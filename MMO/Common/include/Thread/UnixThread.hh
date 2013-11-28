//
// UnixThread.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Oct 24 13:22:02 2013 laurent ansel
// Last update Tue Nov 26 00:42:18 2013 alexis mestag
//

#ifndef 			__UNIXTHREAD_HH__
# define 			__UNIXTHREAD_HH__

#include			<pthread.h>
#include			"Thread/IThread.hh"
#include			"Thread/PthreadCondition.hh"

typedef void *(*CallBack)(void *);

class				UnixThread : public IThread
{
private:
  pthread_t			_thread;
  PthreadCondition		*_cond;
  void				*(*_func)(void *);
  void				*_data;
  bool				_canStart;

  void				setFunc(void *(*func)(void *));
  void				setData(void *data);
  PthreadCondition		*getCond();
  CallBack			getFunc();
  void				*getData();
  void				setCanStart(bool const canStart = true);
  bool				canStart() const;

  static void			*trampoline(void *data);

public:
  UnixThread();
  virtual ~UnixThread();
  virtual bool			create(void *(*func)(void *), void *);
  virtual bool			start();
  virtual bool			exit();
  virtual bool			cancel();
  virtual bool			join();
};

#endif

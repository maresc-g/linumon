//
// MutexVar.hpp for  in /home/maresc_g/Projets/en_cours/rtypeSource
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Nov 14 18:56:32 2013 guillaume marescaux
// Last update Thu Jan 30 14:50:09 2014 guillaume marescaux
//

#ifndef 		__MUTEXVAR_HPP__
# define 		__MUTEXVAR_HPP__

#include		"Mutex/Mutex.hpp"

template<class T>
class			MutexVar
{
private:

  // Attributes
  Mutex			*_mutex;
  T			_var;

public:
  MutexVar(T var):
    _mutex(new Mutex), _var(var)
  {
    _mutex->init();
  }

  virtual ~MutexVar()
  {
    _mutex->destroy();
    delete _mutex;
  }

  void			setVar(T var)
  {
    _mutex->lock();
    _var = var;
    _mutex->unlock();
  }

  T			getVar(void) const
  {
    T			tmp;

    _mutex->lock();
    tmp = _var;
    _mutex->unlock();
    return (tmp);
  }

  T const		operator*(void) const
  {
    return (getVar());
  }

  void			operator=(T const &var)
  {
    setVar(var);
  }
};

#endif

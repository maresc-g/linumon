//
// Mutex.hpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 15:05:48 2013 laurent ansel
// Last update Mon Nov 25 22:55:22 2013 alexis mestag
//

#ifndef 		__MUTEX_HPP__
# define 		__MUTEX_HPP__

# ifdef	_WIN32
#  include		"Mutex/WindowsMutex.hh"
# else
#  include		"Mutex/UnixMutex.hh"
# endif

# ifdef _WIN32
class			Mutex : public	WindowsMutex
# else
class			Mutex : public	UnixMutex
# endif
{
public:
  Mutex():
# ifdef _WIN32
    WindowsMutex()
# else
    UnixMutex()
# endif
  {}
  virtual ~Mutex()
  {}
};

#endif

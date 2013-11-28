//
// Thread.hpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 15:07:30 2013 laurent ansel
// Last update Mon Nov 25 23:05:27 2013 alexis mestag
//

#ifndef 		__THREAD_HPP__
# define 		__THREAD_HPP__

# ifdef	_WIN32
#  include		"Thread/WindowsThread.hh"
# else
#  include		"Thread/UnixThread.hh"
# endif

# ifdef _WIN32
class			Thread : public	WindowsThread
# else
class			Thread : public	UnixThread
# endif
{
public:
  Thread():
# ifdef _WIN32
    WindowsThread()
# else
    UnixThread()
# endif
  {}
  virtual ~Thread()
  {}
};

#endif

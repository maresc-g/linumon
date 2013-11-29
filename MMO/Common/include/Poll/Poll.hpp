//
// Poll.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 19:38:20 2013 laurent ansel
// Last update Thu Nov 28 19:39:17 2013 laurent ansel
//

#ifndef 		__POLL_HPP__
# define		__POLL_HPP__

#ifdef	_WIN32
#include		"Poll/WindowsPoll.hh"
#else
#include		"Poll/UnixPoll.hh"
#endif

#ifdef _WIN32
class			Poll : public	WindowsPoll
#else
class			Poll : public	UnixPoll
#endif
{
public:
  Poll():
#ifdef _WIN32
    WindowsPoll()
#else
    UnixPoll()
#endif
  {}
  virtual ~Poll()
  {}
};

#endif

//
// Socket.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 14:42:30 2013 laurent ansel
// Last update Tue Oct 29 15:06:19 2013 laurent ansel
//

#ifndef 		__SOCKET_HH__
# define 		__SOCKET_HH__

#ifdef	_WIN32
#include		"Socket/WindowsSocket.hh"
#else
#include		"Socket/UnixSocket.hh"
#endif

#ifdef _WIN32
class			Socket : public	WindowsSocket
#else
class			Socket : public	UnixSocket
#endif
{
public:
  Socket():
#ifdef _WIN32
    WindowsSocket()
#else
    UnixSocket()
#endif
  {}
  virtual ~Socket()
  {}
};

#endif

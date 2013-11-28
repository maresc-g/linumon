//
// WindowsSocket.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 13:23:52 2013 laurent ansel
// Last update Tue Nov  5 18:18:35 2013 laurent ansel
//

#ifndef 			__WINDOWSSOCKET_HH__
# define 			__WINDOWSSOCKET_HH__

#ifdef _WIN32

#include			<WinSock2.h>
#include			<iostream>
#include			"Socket/ISocket.hh"

class				WindowsSocket : public ISocket
{
private:
  SOCKET			_socket;
  WSADATA			_wsaData;
  std::string			_proto;
  SocketClient			*_currentSocket;
public:
  WindowsSocket();
  virtual ~WindowsSocket();
  virtual int			initialize(std::string const &);
  virtual int			destroy();
  virtual int			bindSocket(int const);
  virtual int			listenSocket();
  virtual SocketClient const		&getSocket() const;
  virtual SocketClient		*connectToAddr(std::string const &, int const);
  virtual SocketClient		*acceptConnection();
  virtual void			initAddr();
};

#endif

#endif

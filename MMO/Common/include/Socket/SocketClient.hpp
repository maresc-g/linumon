//
// SocketClient.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Oct 29 14:57:01 2013 laurent ansel
// Last update Thu Dec  5 22:25:38 2013 laurent ansel
//

#ifndef 			__SOCKETCLIENT_HH__
# define 			__SOCKETCLIENT_HH__

#ifdef	_WIN32
#include		"Socket/WindowsSocketClient.hh"
#else
#include		"Socket/UnixSocketClient.hh"
#endif

#ifdef _WIN32
class			SocketClient : public	WindowsSocketClient
#else
class			SocketClient : public	UnixSocketClient
#endif
{
public:
  SocketClient(int const socket, std::string const &protocole, struct sockaddr_in *addr = NULL):
#ifdef _WIN32
    WindowsSocketClient(socket, protocole, addr)
#else
    UnixSocketClient(socket, protocole, addr)
#endif
  {}

  SocketClient(SocketClient *client):
#ifdef _WIN32
    WindowsSocketClient(client)
#else
    UnixSocketClient(client)
#endif
  {}

  SocketClient(ISocketClient *client):
#ifdef _WIN32
    WindowsSocketClient(client)
#else
    UnixSocketClient(client)
#endif
  {}
  virtual ~SocketClient()
  {}
};

#endif

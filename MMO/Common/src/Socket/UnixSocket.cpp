//
// UnixSocket.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 13:20:50 2013 laurent ansel
// Last update Fri Feb 28 11:19:10 2014 laurent ansel
//

#ifndef _WIN32

#include			<map>
#include			"Socket/UnixSocket.hh"
#include			"Socket/UnixSocketClient.hh"
#include			"Error/SocketError.hpp"

UnixSocket::UnixSocket():
  _socket(0),
  _currentSocket(NULL)
{

}

UnixSocket::~UnixSocket()
{
  if (this->_currentSocket)
    delete this->_currentSocket;
}

int				UnixSocket::initialize(std::string const &protocole)
{
  static std::map<std::string, int>	protoType =
    {
      {"TCP", SOCK_STREAM},
      {"UDP", SOCK_DGRAM}
    };
  struct protoent		*proto;
  int				yes = 1;

  this->_proto = protocole;
  proto = getprotobyname(protocole.c_str());
  if ((this->_socket = socket(AF_INET, protoType[protocole], proto->p_proto)) == -1)
    {
      throw SocketError("initialize socket failed");
      return (-1);
    }
  if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      throw SocketError("initialize socket failed");
      return (-1);
    }
  if (!this->_currentSocket)
    this->_currentSocket = new SocketClient(this->_socket, this->_proto);
  return (0);
}

int				UnixSocket::destroy()
{
  if (this->_socket == -1)
    return (-1);
  close(this->_socket);
  return (0);
}

int				UnixSocket::bindSocket(int const port)
{
  struct sockaddr_in		sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->_socket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      throw SocketError("bind socket failed");
      close(this->_socket);
      return (-1);
    }
  return (0);
}

int				UnixSocket::listenSocket()
{
  if (listen(this->_socket, SOMAXCONN) == -1)
    {
      throw SocketError("listen socket failed");
      close(this->_socket);
      return (-1);
    }
  return (0);
}

ISocketClient const		&UnixSocket::getSocket() const
{
  return (*this->_currentSocket);
}

ISocketClient			*UnixSocket::connectToAddr(std::string const &addr, int const port)
{
  struct sockaddr_in		*sin = new struct sockaddr_in;
  struct hostent		*host;

  host = gethostbyname(addr.c_str());
  if (!host)
    {
      throw SocketError("server not found");
      return (NULL);
    }
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  sin->sin_addr.s_addr = inet_addr(host->h_name);
  if (this->_proto == "TCP" && (connect(this->_socket, (struct sockaddr *)sin, sizeof(*sin))) == -1)
    {
      throw SocketError("server not found");
      return (NULL);
    }
  this->_currentSocket->setAddr(sin);
  return (this->_currentSocket);
}

ISocketClient			*UnixSocket::acceptConnection()
{
  int				fd;
  unsigned int			size;
  struct sockaddr_in		sin;

  size = sizeof(sin);
  if ((fd = accept(this->_socket, (struct sockaddr *)&sin, (socklen_t *)&size)) == -1)
    return (NULL);
  return (new SocketClient(fd, this->_proto));
}

void				UnixSocket::initAddr()
{
  this->_currentSocket->setAddr(new sockaddr_in);
}

#endif

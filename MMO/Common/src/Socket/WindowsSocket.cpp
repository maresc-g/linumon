//
// WindowsSocket.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 13:21:19 2013 laurent ansel
// Last update Thu Nov 28 19:47:15 2013 laurent ansel
//

#ifdef _WIN32

#include			"Error/SocketError.hpp"
#include			"Socket/WindowsSocket.hh"
#include			"Socket/WindowsSocketClient.hh"

//#pragma comment(lib, "ws2_32.lib")

WindowsSocket::WindowsSocket():
  _socket(0),
  _currentSocket(NULL)
{
  if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
    {
      throw SocketError("WSAStartup failed");
      _socket = -1;
    }
}

WindowsSocket::~WindowsSocket()
{
  if (this->_socket != -1)
    WSACleanup();
}

int				WindowsSocket::initialize(std::string const &protocole)
{
  if (protocole == "TCP")
    _socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
  else if (protocole == "UDP")
    _socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
  this->_proto = protocole;
  if (this->_socket == INVALID_SOCKET)
    {
      throw SocketError("initialize socket failed");
      return (-1);
    }
  if (!this->_currentSocket)
    this->_currentSocket = new SocketClient(this->_socket, this->_proto);
  return (0);
}

int				WindowsSocket::destroy()
{
  if (this->_socket == -1)
    return (-1);
  closesocket(this->_socket);
  return (0);
}

int				WindowsSocket::bindSocket(int const port)
{
  sockaddr_in			addr;
  char				*ip;
  hostent			*thisHost;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  thisHost = gethostbyname("");
  ip = inet_ntoa(*(struct in_addr *)*thisHost->h_addr_list);
  addr.sin_addr.s_addr = inet_addr(ip);
  if (bind(this->_socket, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
      throw SocketError("bind socket failed");
      closesocket(this->_socket);
      return (-1);
    }
  return (0);
}

int				WindowsSocket::listenSocket()
{
  if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
    {
      throw SocketError("listen socket failed");
      closesocket(this->_socket);
      return (-1);
    }
  return (0);
}

ISocketClient const		&WindowsSocket::getSocket() const
{
  return (*this->_currentSocket);
}

ISocketClient			*WindowsSocket::connectToAddr(std::string const &addr, int const port)
{
  sockaddr_in			*addrClient = new sockaddr_in;
  char				*ip;
  hostent			*thisHost;

  addrClient->sin_family = AF_INET;
  addrClient->sin_port = htons(port);
  thisHost = gethostbyname(addr.c_str());
  if (!thisHost)
    {
      throw SocketError("server not found");
      return (NULL);
    }
  ip = inet_ntoa(*(struct in_addr *)*thisHost->h_addr_list);
  addrClient->sin_addr.s_addr = inet_addr(ip);
  if (this->_proto == "TCP" && (WSAConnect(this->_socket, (SOCKADDR *)addrClient, sizeof(*addrClient), NULL, NULL, NULL, NULL)) == SOCKET_ERROR)
    {
      throw SocketError("server not found");
      return (NULL);
    }
  this->_currentSocket->setAddr(addrClient);
  return (this->_currentSocket);
}

ISocketClient			*WindowsSocket::acceptConnection()
{
  struct sockaddr_in		client;
  int				size = sizeof(client);
  SOCKET			socketClient;

  if ((socketClient = WSAAccept(this->_socket, (SOCKADDR*)&client, &size, NULL, NULL)) != SOCKET_ERROR)
    return (new SocketClient(socketClient, this->_proto));
  return (NULL);
}

void				WindowsSocket::initAddr()
{
   this->_currentSocket->setAddr(new sockaddr_in);
}

#endif

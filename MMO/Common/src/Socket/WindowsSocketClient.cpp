//
// WindowsSocketClient.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 15:26:41 2013 laurent ansel
// Last update Wed Dec  4 13:43:47 2013 laurent ansel
//

#ifdef _WIN32

#include		<iostream>
#include		<string.h>
#include		"Socket/WindowsSocketClient.hh"

WindowsSocketClient::WindowsSocketClient(SOCKET const socket, std::string const &protocole, struct sockaddr_in *addr):
  _socket(socket),
  _proto(protocole),
  _addr(new struct sockaddr_in)
{
  if (addr)
    {
      this->_addr->sin_family = addr->sin_family;
      this->_addr->sin_port = addr->sin_port;
      this->_addr->sin_addr.s_addr = addr->sin_addr.s_addr;
    }
}

WindowsSocketClient::WindowsSocketClient(WindowsSocketClient *client)
{
  *this = client;
}

WindowsSocketClient::~WindowsSocketClient()
{
  if (this->_addr)
    delete this->_addr;
}


WindowsSocketClient	&WindowsSocketClient::operator=(WindowsSocketClient *client)
{
  if (this != client)
    {
      this->_socket = client->getSocket();
      this->_proto = client->getProto();
      this->_addr = new struct sockaddr_in;
      this->setAddr(client->getAddr());
    }
  return (*this);
}

int			WindowsSocketClient::readSocket(char *buf, int const size) const
{
  DWORD			ret = 0;
  WSABUF		dataBuf;
  DWORD			lp = 0;
  int			addrlen = sizeof(*this->_addr);

  dataBuf.len = SIZE_BUFFER;
  dataBuf.buf = buf;
  if (this->_proto == "UDP")
    {
      if (WSARecvFrom(this->_socket, &dataBuf, 1, &ret, &lp, (SOCKADDR *)this->_addr, &addrlen, NULL, NULL) == SOCKET_ERROR)
	return (-1);
    }
  else
    if (WSARecv(this->_socket, &dataBuf, 1, &ret, &lp, NULL, NULL) == SOCKET_ERROR)
      return (-1);
  //   std::cout << this->_addr->sin_family << std::endl;
  //    	std::cout << "READ = ";
  // std::cout.write(buf, ret);
  // std::cout << std::endl;
  return (ret);
}

int			WindowsSocketClient::writeSocket(char *buf, int const size) const
{
  char			tmp[SIZE_BUFFER];
  DWORD			ret = 0;
  WSABUF		dataBuf;
  DWORD			lp = 0;
  int			addrlen = sizeof(*this->_addr);

  // std::cout << "buffer = ";
  // std::cout.write(buf, size);
  // std::cout << std::endl;
  dataBuf.len = size;
  dataBuf.buf = buf;
  if (this->_proto == "UDP")
    {
      if (WSASendTo(this->_socket, &dataBuf, 1, &ret, lp, (SOCKADDR *)this->_addr, addrlen, NULL, NULL) == SOCKET_ERROR)
	return (-1);
    }
  else
    if (WSASend(this->_socket, &dataBuf, 1, &ret, lp, NULL, NULL) == SOCKET_ERROR)
      return (-1);
  return (ret);
}

void			WindowsSocketClient::closeSocket() const
{
  closesocket(this->_socket);
}

int			WindowsSocketClient::getSocket() const
{
  return (this->_socket);
}

void			WindowsSocketClient::setAddr(struct sockaddr_in *addr)
{
  if (addr)
    {
      this->_addr->sin_family = addr->sin_family;
      this->_addr->sin_port = addr->sin_port;
      this->_addr->sin_addr.s_addr = addr->sin_addr.s_addr;
    }
}

struct sockaddr_in	*WindowsSocketClient::getAddr() const
{
  return (this->_addr);
}

std::string const	&WindowsSocketClient::getProto() const
{
  return (this->_proto);
}

#endif

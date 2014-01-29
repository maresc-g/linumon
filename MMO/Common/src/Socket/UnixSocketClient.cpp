//
// UnixSocketClient.cpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 15:26:32 2013 laurent ansel
// Last update Fri Jan 24 15:40:32 2014 guillaume marescaux
//

#ifndef _WIN32

#include		<iostream>
#include		"Socket/UnixSocketClient.hh"

UnixSocketClient::UnixSocketClient(int const socket, std::string const &protocole, struct sockaddr_in *addr):
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

UnixSocketClient::UnixSocketClient(UnixSocketClient *client)
{
  *this = client;
}

UnixSocketClient::UnixSocketClient(ISocketClient *client)
{
  *this = client;
}

UnixSocketClient	&UnixSocketClient::operator=(UnixSocketClient *client)
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

UnixSocketClient	&UnixSocketClient::operator=(ISocketClient *client)
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

UnixSocketClient::~UnixSocketClient()
{
  if (this->_addr)
    delete this->_addr;
}

int			UnixSocketClient::readSocket(char *buf, int const size) const
{
  int			ret = 0;
  socklen_t		addrlen = sizeof(*this->_addr);

  if (this->_proto == "UDP")
    ret = recvfrom(this->_socket, buf, size, 0, (struct sockaddr *)this->_addr, &addrlen);
  else
    ret = recv(this->_socket, buf, size, MSG_DONTWAIT);
  if (ret > 0)
    {
      std::cout << "READ : [";
      std::cout.write(buf, ret);
      std::cout << "]" << std::endl;
    }
  return (ret);
}

int			UnixSocketClient::writeSocket(char *buf, int const size) const
{
  int			ret = 0;
  socklen_t		addrlen = sizeof(*this->_addr);

  std::cout << "WRITE : [";
  std::cout.write(buf, size);
  std::cout << "]" << std::endl;
  if (this->_proto == "UDP")
    ret = sendto(this->_socket, buf, size, 0, (struct sockaddr *)this->_addr, addrlen);
  else
    ret = send(this->_socket, buf, size, MSG_DONTWAIT);
  return (ret);
}

void			UnixSocketClient::closeSocket() const
{
  close(this->_socket);
}

int			UnixSocketClient::getSocket() const
{
  return (this->_socket);
}

void			UnixSocketClient::setAddr(struct sockaddr_in *addr)
{
  if (addr)
    {
      this->_addr->sin_family = addr->sin_family;
      this->_addr->sin_port = addr->sin_port;
      this->_addr->sin_addr.s_addr = addr->sin_addr.s_addr;
    }
}

struct sockaddr_in	*UnixSocketClient::getAddr() const
{
  return (this->_addr);
}

std::string const	&UnixSocketClient::getProto() const
{
  return (this->_proto);
}

#endif

//
// WindowsSocketClient.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 15:22:49 2013 laurent ansel
// Last update Tue Nov  5 18:17:25 2013 laurent ansel
//

#ifndef			__WINDOWSSOCKETCLIENT_HH__
# define		__WINDOWSSOCKETCLIENT_HH__

#ifdef _WIN32

#include		<WinSock2.h>
#include		"Socket/ISocketClient.hh"

#pragma comment(lib, "ws2_32.lib")

class			WindowsSocketClient : public ISocketClient
{
private:
  SOCKET		_socket;
  std::string		_proto;
  struct sockaddr_in	*_addr;
public:
  WindowsSocketClient(SOCKET const fd, std::string const &protocole, struct sockaddr_in *addr = NULL);
  virtual ~WindowsSocketClient();
  virtual int		readSocket(char *data, int const size) const;
  virtual int		writeSocket(char *data, int const size) const;
  virtual void		closeSocket() const;
  virtual int		getSocket() const;
  virtual void		setAddr(struct sockaddr_in *addr);
  virtual struct sockaddr_in	*getAddr() const;
};

#endif

#endif

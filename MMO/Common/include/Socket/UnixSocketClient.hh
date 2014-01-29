//
// UnixSocketClient.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 15:22:40 2013 laurent ansel
// Last update Wed Jan 29 17:18:14 2014 laurent ansel
//

#ifndef 			__UNIXSOCKETCLIENT_HH__
# define 			__UNIXSOCKETCLIENT_HH__

#ifndef _WIN32

#include			<unistd.h>
#include			<sys/types.h>
#include			<sys/types.h>
#include			<netdb.h>
#include			<sys/types.h>
#include			<netinet/in.h>
#include			<arpa/inet.h>
#include			"Socket/ISocketClient.hh"

class				UnixSocketClient : public ISocketClient
{
private:
  int				_socket;
  std::string			_proto;
  struct sockaddr_in		*_addr;
public:
  UnixSocketClient(int const fd, std::string const &protocole, struct sockaddr_in *addr = NULL);
  UnixSocketClient(UnixSocketClient *client);
  UnixSocketClient(ISocketClient const *client);
  virtual ~UnixSocketClient();
  UnixSocketClient		&operator=(UnixSocketClient *client);
  UnixSocketClient		&operator=(ISocketClient const *client);
  virtual int			readSocket(char *data, int const size) const;
  virtual int			writeSocket(char *data, int const size) const;
  virtual void			closeSocket() const;
  virtual int			getSocket() const;
  virtual void			setAddr(struct sockaddr_in *addr);
  virtual struct sockaddr_in	*getAddr() const;
  virtual std::string const	&getProto() const;
};

#endif

#endif

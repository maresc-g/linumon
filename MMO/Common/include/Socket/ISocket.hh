//
// ISocket.hh for  in /home/ansel_l/Documents/Rtype/rtype
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 16:36:48 2013 laurent ansel
// Last update Thu Nov 28 19:46:11 2013 laurent ansel
//

#ifndef 			__ISOCKET_HH__
# define 			__ISOCKET_HH__

#include			<string>
#include			"Socket/SocketClient.hpp"

class				ISocket
{
public:
  virtual ~ISocket(){}
  virtual int			initialize(std::string const &) = 0;
  virtual int			destroy() = 0;
  virtual int			bindSocket(int const) = 0;
  virtual int			listenSocket() = 0;
  virtual ISocketClient const	&getSocket() const = 0;
  virtual ISocketClient		*connectToAddr(std::string const &, int const) = 0;
  virtual ISocketClient		*acceptConnection() = 0;
  virtual void			initAddr() = 0;
};

#endif

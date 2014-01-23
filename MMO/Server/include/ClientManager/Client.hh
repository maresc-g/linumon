//
// Client.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:58:04 2013 laurent ansel
// Last update Tue Dec 10 10:42:31 2013 laurent ansel
//

#ifndef 			__CLIENT_HH__
# define 			__CLIENT_HH__

#include			<string>
#include			<map>
#include			"Trame/Trame.hh"
#include			"Socket/SocketClient.hpp"
#include			"Crypto/Crypto.hh"

class				Client
{
private:
  bool				_use;
  FD				_id;
  std::map<std::string, ISocketClient *>	*_sockets;
  int				_trame;
public:
  Client();
  virtual ~Client();
  void				clear();
  bool				isUse() const;
  void				use(FD const fd);
  FD				getId() const;
  void				setSocket(ISocketClient *socket, std::string const &proto);
  bool				writeTrame(Trame *trame, std::string const &proto);
  bool				readTrame(std::string &str, std::string const &proto);
  void				addTrame(unsigned int const nb);
  unsigned int			getNbTrame() const;
};

#endif
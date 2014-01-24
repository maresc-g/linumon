//
// Core.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:57:49 2014 guillaume marescaux
// Last update Fri Jan 24 15:17:12 2014 guillaume marescaux
//

#ifndef 		__CORE_HH__
# define 		__CORE_HH__

#include		<map>
#include		<string>
#include		"Trame/Trame.hh"
#include		"Socket/Socket.hpp"
#include		"Entities/Player.hh"
#include		"Poll/Poll.hpp"

class			Core
{
public:

  enum			eSocket
    {
      TCP,
      UDP
    };

  struct		ConnectionInfos
  {
    std::string		ip;
    int			port;
  };

private:

  // Attributes
  std::map<eSocket, Socket *>           *_sockets;
  std::map<eSocket, ISocketClient *>    *_socketsClient;
  ConnectionInfos			*_infos;
  Player				*_player;
  Poll					*_poll;

public:

  // Ctor / Dtor
  Core();
  virtual ~Core();

private:

  Core(Core const &);
  Core			&operator=(Core const &);
};

#endif

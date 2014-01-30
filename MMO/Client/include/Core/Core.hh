//
// Core.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:57:49 2014 guillaume marescaux
// Last update Thu Jan 30 12:40:53 2014 guillaume marescaux
//

#ifndef 		__CORE_HH__
# define 		__CORE_HH__

#include		<map>
#include		<string>
#include		"Trame/Trame.hh"
#include		"Socket/Socket.hpp"
#include		"Entities/Player.hh"
#include		"Poll/Poll.hpp"
#include		"Protocol/Protocol.hpp"

# define		CONNECT_FILE	"Res/Connection.json"

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
  Protocol				*_proto;
  int					_id;
  bool					_initialized;

public:

  // Ctor / Dtor
  Core();
  virtual ~Core();

  // Methods
  void			init(void);
  void			read(int const timeout, bool const setTimeout);
  void			write();
  void			connection(std::string const &pseudo, std::string const &pass);

private:

  Core(Core const &);
  Core			&operator=(Core const &);

  void			readFromSocket(eSocket sock);
  void			writeToSocket(Trame const &trame, eSocket sock);
  bool			welcome(Trame *trame);
  bool			check(Trame *trame);
};

#endif

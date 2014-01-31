//
// Core.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:57:49 2014 guillaume marescaux
// Last update Fri Jan 31 11:29:24 2014 guillaume marescaux
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
#include		"Protocol/LoginInfos.hpp"
#include		"Thread/Thread.hpp"
#include		"Mutex/MutexVar.hpp"
#include		"eState.hh"

# define		CONNECT_FILE	"Res/Connection.json"

class			Core : public Thread
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
  MutexVar<bool>			*_initialized;
  MutexVar<bool>			*_running;
  MutexVar<eState>			*_state;

public:

  // Ctor / Dtor
  Core(MutexVar<eState> *state);
  virtual ~Core();

  // Methods
  void			init(void);
  void			read(int const timeout, bool const setTimeout);
  void			write();
  void			connection(LoginInfos *infos);
  void			run(void);
  void			loop(void);
  void			quit(void);

private:

  Core(Core const &);
  Core			&operator=(Core const &);

  void			readFromSocket(eSocket sock);
  void			writeToSocket(Trame const &trame, eSocket sock);
  bool			welcome(Trame *trame);
  bool			check(Trame *trame);
  bool			handlerError(Trame *trame);
};

#endif

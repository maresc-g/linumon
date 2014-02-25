//
// Core.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:57:49 2014 guillaume marescaux
// Last update Tue Feb 25 11:21:09 2014 guillaume marescaux
//

#ifndef 		__CORE_HH__
# define 		__CORE_HH__

#include		<map>
#include		<string>
#include		"Trame/Trame.hh"
#include		"Socket/Socket.hpp"
#include		"Entities/Views/PlayerView.hh"
#include		"Poll/Poll.hpp"
#include		"Protocol/Protocol.hpp"
#include		"Thread/Thread.hpp"
#include		"Mutex/MutexVar.hpp"
#include		"Common/eState.hh"
#include		"Common/eDirection.hh"
#include		"ErrorHandler.hh"
#include		"Entities/Faction.hh"
#include		"Chat/Chat.hh"

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
  Poll					*_poll;
  Protocol				*_proto;
  int					_id;
  MutexVar<bool>			*_initialized;
  MutexVar<bool>			*_running;
  MutexVar<CLIENT::eState>		*_state;
  MutexVar<Player *>			*_player;
  MutexVar<std::list<PlayerView *> *>	*_players;
  MutexVar<Chat *>			*_chat;
  ErrorHandler				*_handler;

public:

  // Ctor / Dtor
  Core(MutexVar<CLIENT::eState> *state, MutexVar<Player *> *player, MutexVar<std::list<PlayerView *> *> *players,
       MutexVar<Chat *> *chat);
  virtual ~Core();

  // Methods
  void			init(void);
  void			read(int const timeout, bool const setTimeout);
  void			write();

  void			connection(std::string const &pseudo, std::string const &pass);
  void			choosePlayer(PlayerView const &player);
  void			createPlayer(std::string const &name, std::string const &faction);
  void			run(void);
  void			loop(void);
  void			quit(void);
  bool			move(CLIENT::eDirection dir);
  void			sendChat(std::string const &msg);
  void			spell(unsigned int idBattle, Spell const &spell, unsigned int target);
  void			capture(unsigned int idBattle, unsigned int target);
  void			sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob);
  //  void			stuff(void *action);
  // void			talents();
  // void			craft();
  // void			gather();
  void			useObject(unsigned int target, AItem const &item);
  // void			unsigned interaction();
  void			putItem(AItem const &item);
  void			getItem(AItem const &item);
  void			sendMoney(unsigned int money);
  void			accept(void);
  void			refuse(void);
  void			heal(void);
  void			disconnect(void);
  void			switchPlayer(void);

private:

  Core(Core const &);
  Core			&operator=(Core const &);

  void			readFromSocket(eSocket sock);
  void			writeToSocket(Trame const &trame, eSocket sock);

  bool			welcome(Trame *trame);
  bool			check(Trame *trame);
  bool			handleError(Trame *trame);
  bool			playerlist(Trame *trame);
  bool			player(Trame *trame);
  bool			map(Trame *trame);
  bool			getChat(Trame *trame);
  bool			launchBattle(Trame *);
  bool			spell(Trame *);
  bool			spellEffect(Trame *);
  bool			captureEffect(Trame *);
  bool			switchMob(Trame *);
  bool			deadMob(Trame *);
  bool			endBattle(Trame *);
  bool			upStats(Trame *);
  bool			upTalents(Trame *);
  bool			inventory(Trame *);
  bool			job(Trame *);
  bool			caseMap(Trame *);
  bool			objectEffect(Trame *);
  bool			launchTrade(Trame *);
  bool			putItem(Trame *);
  bool			getItem(Trame *);
  bool			getMoney(Trame *);
  bool			accept(Trame *);
  bool			refuse(Trame *);
  bool			quitServer(Trame *);
  bool			removeEntity(Trame *);
  bool			entity(Trame *);
  bool			newPlayer(Trame *);
  bool			newZone(Trame *);
};

#endif

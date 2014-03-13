//
// Core.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:57:49 2014 guillaume marescaux
// Last update Wed Mar 12 16:55:48 2014 guillaume marescaux
//

#ifndef 		__CORE_HH__
# define 		__CORE_HH__

# include		<map>
# include		<string>
# include		"Trame/Trame.hh"
# include		"Socket/Socket.hpp"
# include		"Entities/Views/PlayerView.hh"
# include		"Poll/Poll.hpp"
# include		"Protocol/Protocol.hpp"
# include		"Thread/Thread.hpp"
# include		"Mutex/MutexVar.hpp"
# include		"Common/eState.hh"
# include		"Common/eDirection.hh"
# include		"ErrorHandler.hh"
# include		"Entities/Faction.hh"
# include		"Chat/Chat.hh"
# include		"Battle/Battle.hh"
# include		"Trade/Trade.hh"
# include		"Utility/CommonDefine.hh"

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
  MutexVar<bool>			*_newPlayer;
  MutexVar<Battle *>			*_battle;
  MutexVar<Trade *>			*_trade;
  ErrorHandler				*_handler;

public:

  // Ctor / Dtor
  Core(MutexVar<CLIENT::eState> *state, MutexVar<Player *> *player, MutexVar<std::list<PlayerView *> *> *players,
       MutexVar<Chat *> *chat, MutexVar<bool> *newPlayer, MutexVar<Battle *> *battle, MutexVar<Trade *> *trade);
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
  void			spell(unsigned int idBattle, Spell const &spell, unsigned int launcher, unsigned int target);
  void			capture(unsigned int idBattle, unsigned int target);
  void			sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob);
  void			stuff(int action, unsigned int idItem, unsigned int target);
  // void			talents();
  void			craft(std::string const &craftName, std::string const &jobName);
  // void			gather();
  void			useObject(unsigned int target, unsigned int item);
  // void			unsigned interaction();
  void			putItem(unsigned int idTrade, unsigned int idItem);
  void			getItem(unsigned int idTrade, unsigned int idItem);
  void			putMob(unsigned int idTrade, unsigned int idMob);
  void			getMob(unsigned int idTrade, unsigned int idMob);
  void			putMoney(unsigned int idTrade, unsigned int money);
  void			getMoney(unsigned int idTrade, unsigned int money);
  void			mobtoBattleMob(unsigned int idMob);
  void			battleMobtoMob(unsigned int idMob);
  void			switchMobs(unsigned int idMob1, unsigned int idMob2);
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
  bool			turnTo(Trame *);
  bool			spell(Trame *);
  bool			spellEffect(Trame *);
  bool			captureEffect(Trame *);
  bool			switchMob(Trame *);
  bool			deadMob(Trame *);
  bool			endBattle(Trame *);
  bool			upStats(Trame *);
  bool			upTalents(Trame *);
  bool			addToInventory(Trame *);
  bool			deleteFromInventory(Trame *);
  bool			job(Trame *);
  bool			caseMap(Trame *);
  bool			objectEffect(Trame *);
  bool			launchTrade(Trame *);
  bool			putItem(Trame *);
  bool			getItem(Trame *);
  bool			putMob(Trame *);
  bool			getMob(Trame *);
  bool			putMoney(Trame *);
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

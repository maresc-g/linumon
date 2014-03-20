//
// ClientManager.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:57:38 2013 laurent ansel
// Last update Wed Mar 19 19:25:46 2014 laurent ansel
//

#ifndef 			__CLIENTMANAGER_HH__
# define 			__CLIENTMANAGER_HH__

#include			<vector>
#include			<map>
#include			<utility>
#include			<boost/function.hpp>
#include			"ClientManager/ClientUpdater.hh"
#include			"Utility/Singleton.hpp"
#include			"Thread/Thread.hpp"

#define	NB_CLIENTS_PER_THREAD	200
#define	CLIENT_THREAD_MIN	10

class				ClientManager : public Singleton<ClientManager>
{
  friend class			Singleton<ClientManager>;

private:
  std::vector<std::pair<ClientUpdater *, bool> >	*_updaters;
  Mutex				*_mutex;
  ClientManager();
  virtual ~ClientManager();

public:
  void				newClient(Header const &header, ISocketClient *tcp);
  void				setInfoClient(FD const fd, ISocketClient const *socket, std::string const &proto) const;
  void				setInfoClient(FD const fd) const;
  void				setInfoClient(FD const fd, std::string const &protocole, bool const read) const;
  void				setInfoClient(FD const fd, std::string const &name, Faction *faction, bool &ok) const;
  void				setInfoClient(FD const fd, unsigned int const idPlayer) const;
  void				setInfoClient(FD const fd, User *user) const;
  void				setInfoClient(FD const fd, Player::PlayerCoordinate *coord) const;
  void				sendListPlayers(FD const fd) const;
  void				setPlayerTalent(FD const fd, std::string const &talent, unsigned int const pts) const;
  void				playerObject(FD const fd, unsigned int const target, unsigned int const item) const;
  void				playerObject(FD const fd, unsigned int const item, int const nb) const;
  void				merge(FD const fd, unsigned int const idStack, unsigned int const idStack2) const;
  void				newStack(FD const fd, unsigned int const idStack, unsigned int const nb) const;

  void				modifyDigitaliser(FD const fd, unsigned int const idMob1, unsigned int const idMob2, bool const tobattleMob) const;

  void				newGuild(FD const fd, Guild *guild) const;
  bool				inGuild(FD const fd) const;

  void				startBattle(FD const fd, Player *&player) const;
  void				endBattle(FD const fd) const;
  void				startTrade(FD const fd, Player *&player) const;
  void				endTrade(FD const fd) const;

  void				newState(FD const fd, Client::eState const state) const;

  void				sendAllInformationModel(FD const fd) const;
  bool				stuff(FD const fd, bool const get, unsigned int const idItem, unsigned int const target) const;

  bool				craftSomething(FD const fd, std::string const &craft, std::string const &job) const;
  bool				gatherSomething(FD const fd, std::string const &job, unsigned int const gather, unsigned int const carcass) const;

private:
  void				findWrite() const;
  bool				moveEntity(Trame * trame);
  bool				connectionUser(Trame * trame);
  bool				createPlayer(Trame * trame);
  bool				choosePlayer(Trame * trame);
  bool				disconnectUser(Trame * trame);
  bool				disconnectPlayer(Trame * trame);
  bool				userAlreadyConnected(FD const fd, User *user) const;
  void				initializeProtocolFunction() const;
};

#endif

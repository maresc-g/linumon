//
// ClientUpdater.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 11:19:28 2013 laurent ansel
// Last update Mon Mar 24 14:30:40 2014 antoine maitre
//

#ifndef 			__CLIENTUPDATER_HH__
# define 			__CLIENTUPDATER_HH__

#include			<list>
#include			<utility>
#include			"ClientManager/Client.hh"
#include			"Thread/Thread.hpp"
#include			"Mutex/Mutex.hpp"
#include			"Header/Header.hh"
#include			"CodeBreaker/CodeBreaker.hh"
#include			"ClientManager/ReadWriteAction.hh"

class				ClientUpdater : public Thread
{
private:
  Mutex				*_mutex;
  bool				_quit;
  std::map<Client *, std::list<ReadWriteAction * > * >	*_action;

public:
  ClientUpdater(unsigned int const nbClient);
  virtual ~ClientUpdater();
  void				run();
  void				setQuit(bool const quit);
  bool				newClient(Header const &header, ISocketClient *client);
  bool				setInfo(FD const fd, ISocketClient const *client, std::string const &proto) const;
  bool				setInfo(FD const fd, bool const disconnect) const;
  bool				setInfo(FD const fd, std::string const &name, Faction *Faction, bool &ok) const;
  bool				setInfo(FD const fd, unsigned int const idPlayer, bool const send) const;
  bool				setInfo(FD const fd, User *user) const;
  bool				setInfo(FD const fd, Player::PlayerCoordinate *coord) const;
  bool				sendListPlayers(FD const fd) const;
  void				readClient(FD const fd, std::string const &protocole);
  void				canWrite(FD const fd, std::string const &protocole);
  bool				search(FD const fd) const;
  void				getClients(std::list<FD> &list) const;
  bool				setTalents(FD const fd, std::string const &talent, unsigned int const pts) const;
  bool				playerObject(FD const fd, unsigned int const target, unsigned int const item) const;
  bool				playerObject(FD const fd, unsigned int const item, int const nb) const;

  bool				newGuild(FD const fd, Guild *guild) const;
  bool				newGuild(std::string const &playerName, Guild *guild) const;
  bool				inviteInGuild(std::string const &playerName, std::string const &guild) const;
  bool				inGuild(FD const fd, bool &guild) const;

  bool				merge(FD const fd, unsigned int const idStack, unsigned int const idStack2) const;
  bool				newStack(FD const fd, unsigned int const idStack, unsigned int const nb) const;

  bool				modifyDigitaliser(FD const fd, unsigned int const idMob1, unsigned int const idMob2, bool const tobattleMob) const;

  bool				stateBattle(FD const fd, bool const start, bool const end, Player *&player) const;
  bool				stateTrade(FD const fd, bool const start, bool const end, Player *&player) const;

  void				newState(FD const fd, Client::eState const state) const;

  void				sendAllInformationModel(FD const fd) const;
  bool				stuff(FD const fd, bool const get, unsigned int const idItem, unsigned int const target) const;

  void				heal(FD const fd) const;

  bool				craftSomething(FD const fd, std::string const &craft, std::string const &job) const;
  bool				gatherSomething(FD const fd, unsigned int const gather, std::string const &job, unsigned int const carcass) const;

  bool				disconnectUser(FD const fd) const;
  bool				disconnectPlayer(FD const fd) const;

private:
  void				readTrame(Client *client, std::string const &protocole) const;
  void				writeTrame(Client *client, std::string const &protocole) const;
  void				check();
};

void				*runClientUpdater(void *data);

#endif

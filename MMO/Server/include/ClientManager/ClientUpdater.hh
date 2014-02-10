//
// ClientUpdater.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 11:19:28 2013 laurent ansel
// Last update Mon Feb 10 14:24:46 2014 laurent ansel
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
  bool				setTalents(Trame *trame) const;

private:
  void				readTrame(Client *client, std::string const &protocole) const;
  void				writeTrame(Client *client, std::string const &protocole) const;
  void				check();
};

void				*runClientUpdater(void *data);

#endif

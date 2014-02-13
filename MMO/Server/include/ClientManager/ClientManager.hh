//
// ClientManager.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:57:38 2013 laurent ansel
// Last update Wed Feb 12 19:51:25 2014 laurent ansel
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
  void				setPlayerTalents(Trame *trame) const;
  void				playerObject(FD const fd, unsigned int const target, unsigned int const item) const;
  void				playerObject(FD const fd, unsigned int const item) const;

  void				startBattle(FD const fd) const;
  void				endBattle(FD const fd) const;
  void				startTrade(FD const fd) const;
  void				endTrade(FD const fd) const;

private:
  void				findWrite() const;
  bool				moveEntity(Trame * trame);
  bool				connectionUser(Trame * trame);
  bool				createPlayer(Trame * trame);
  bool				choosePlayer(Trame * trame);
  bool				userAlreadyConnected(FD const fd, User *user) const;
  void				initializeProtocolFunction() const;
};

#endif

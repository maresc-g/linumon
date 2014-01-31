//
// ClientManager.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:57:38 2013 laurent ansel
// Last update Thu Jan 30 14:40:26 2014 laurent ansel
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

//typedef /*boost*/std::function<void (FD const)> function;
typedef void (function)(FD const);

class				ClientManager : public Singleton<ClientManager>, public Thread
{
  friend class			Singleton<ClientManager>;

private:
  std::vector<std::pair<ClientUpdater *, bool> >	*_updaters;
  function			*_serverWriteFunc;
  bool				_quit;
  Mutex				*_mutex;
  ClientManager();
  virtual ~ClientManager();
public:
  void				run();
  void				setQuit(bool const quit);
  void				newClient(Header const &header, ISocketClient *tcp);
  void				setInfoClient(FD const fd, ISocketClient const *socket, std::string const &proto) const;
  void				setInfoClient(FD const fd) const;
  void				setInfoClient(FD const fd, std::string const &protocole, bool const read) const;
  void				setInfoClient(FD const fd, std::string const &name, std::string const &faction, bool &ok) const;
  void				setInfoClient(FD const fd, unsigned int const idPlayer) const;
  void				setInfoClient(FD const fd, User *user) const;
  void				setWriteFunction(function *writeFunc);
  void				newTrameToWrite(FD const fd, unsigned int const nbTrame) const;
private:
  void				findWrite() const;
  bool				connectionUser(Trame * trame);
  bool				createPlayer(Trame * trame);
  bool				choosePlayer(Trame * trame);
};

void				*runClientManager(void *data);

#endif

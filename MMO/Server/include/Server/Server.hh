//
// Server.hh for  in /home/ansel_l/Documents/Rtype/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 20:01:50 2013 laurent ansel
// Last update Wed Mar  5 15:37:00 2014 laurent ansel
//

#ifndef 			__SERVER_HH__
# define 			__SERVER_HH__

#define DEBUG_SERVER

#include			<map>
#include			<string>
#include			"Header/Header.hh"
#include			"Socket/Socket.hpp"
#include			"Mutex/Mutex.hpp"
#include			"Thread/Thread.hpp"
#include			"Poll/Poll.hpp"
#include			"Utility/Singleton.hpp"
#include			"ClientManager/ClientManager.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"Crypto/Crypto.hh"
#include			"Utility/FunctorContainer.hpp"
#include			"Mutex/MutexVar.hpp"
#include			"ClientWriter/ClientWriter.hh"
#include			"GameProtocol/GameProtocol.hh"

class				Server : public Singleton<Server>
{
  friend class			Singleton<Server>;

private:
  std::map<std::string, Socket *>	*_socket;
  Poll				*_poll;
  std::map<FD, std::pair<bool, bool> >	*_actionServer; /*[client] = {write, disconnect}*/
  Mutex				*_mutex;
  Mutex				*_protoMutex;
  CodeBreaker			*_codeBreaker;
  Protocol			*_protocol;
  GameProtocol			*_gameProtocol;

  Server(/*int const port*/);
  virtual ~Server();

public:
  void				run();
  void				detectWrite(FD const fd);
  void				init(int const port);

  template<typename ... P>
  bool				callProtocol(std::string const &key, unsigned int const id, P ... params)
  {
    bool				ret = false;

    this->_protoMutex->lock();
    ret = this->_protocol->operator()<unsigned int const, P ...>(key, id, params ...);
    if (ret)
      ClientWriter::getInstance()->addNewTrame(id, 1);
    this->_protoMutex->unlock();
    return (ret);
  }

  bool				callProtocol(Trame *trame);
  bool				addFuncProtocol(std::string const &key, std::function<bool (Trame *)> func);

private:
  void				initializePoll() const;
  void				runPoll() const;
  void				debug(std::string const &str) const;
  void				actionServer();
  void				actionClient();
  bool				acceptNewClient();
  bool			        disconnect();
  bool				readSomething(std::map<FD, std::pair<bool, bool> >::iterator &it);
  bool			        writeSomething(std::map<FD, std::pair<bool, bool> >::iterator &it);
  bool			        disconnectClient(std::map<FD, std::pair<bool, bool> >::iterator &it);
  bool				recvUdp();
};

template<typename T, typename R, typename... P>
struct				s_func
{
  T				_type;
  R				(Server::*func)(P...);
};

#endif

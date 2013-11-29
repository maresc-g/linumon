//
// Server.hh for  in /home/ansel_l/Documents/Rtype/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 20:01:50 2013 laurent ansel
// Last update Fri Nov 29 15:38:29 2013 laurent ansel
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

class				Server
{
private:
  unsigned int			_clientId;
  std::map<std::string, Socket *>	*_socket;
  Poll				*_poll;
public:
  Server(int const port);
  virtual ~Server();
  void				run();
private:
  void				initializePoll() const;
  void				runPoll() const;
  void				debug(std::string const &str) const;
};

#endif

//
// ClientWriter.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 12:29:20 2014 laurent ansel
// Last update Thu Feb  6 12:59:26 2014 laurent ansel
//

#ifndef 			__CLIENTWRITER_HH__
# define 			__CLIENTWRITER_HH__

#include			"Utility/Singleton.hpp"
#include			"Thread/Thread.hpp"
#include			"ClientManager/Client.hh"
#include			"Mutex/Mutex.hpp"

class				ClientWriter : public Singleton<ClientWriter>, public Thread
{
  friend			Singleton<ClientWriter>;

private:
  std::map<FD, unsigned int>	*_write;
  bool				_quit;
  Mutex				*_mutex;

  ClientWriter();
  virtual ~ClientWriter();

public:
  void				run();
  void				setQuit(bool const quit);
  void				newClient(FD const fd);
  void				deleteClient(FD const fd);
  unsigned int			getNbTrame(FD const fd) const;
  void				addNewTrame(FD const fd, unsigned int const nb);
};

void				*runClientWriter(void *data);

#endif

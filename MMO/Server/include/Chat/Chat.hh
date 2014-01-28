//
// Chat.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Jan 28 13:12:37 2014 laurent ansel
// Last update Tue Jan 28 14:04:43 2014 laurent ansel
//

#ifndef 			__CHAT_HH__
# define 			__CHAT_HH__

# include			<utility>
# include			<list>
# include			"Utility/Singleton.hpp"
# include			"Thread/Thread.hpp"
# include			"Trame/Trame.hh"
# include			"Mutex/Mutex.hpp"

# define DEFAULT_STORAGE_CHAT	100

class				Chat : public Thread, public Singleton<Chat>
{
  friend class			Singleton<Chat>;
private:
  std::list<std::pair<bool, Trame *> > *_msg;
  bool				_quit;
  Mutex				*_mutex;
  Chat();
  virtual ~Chat();
public:
  void				run();
  void				setQuit(bool const quit);
  bool				newMsg(Trame *trame);
};

void				*runChat(void *data);

#endif

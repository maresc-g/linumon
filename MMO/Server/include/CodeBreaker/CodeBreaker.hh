//
// CodeBreaker.hh for  in /home/ansel_l/Documents/Pfa/work/Server/include
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  1 14:35:59 2013 laurent ansel
// Last update Sun Dec 15 15:51:16 2013 laurent ansel
//

#ifndef 			__CODEBREAKER_HH__
# define 			__CODEBREAKER_HH__

#include			<list>
#include			<map>
#include			<utility>
#include			"Trame/Trame.hh"
#include			"Thread/Thread.hpp"
#include			"Utility/Singleton.hpp"
#include			"ObjectPool/ObjectPool.hpp"
#include			"CircularBufferManager/CircularBufferManager.hh"
#include			"Protocol/Protocol.hpp"

class				CodeBreaker : public Thread
{
private:
  Protocol<std::string>		*_protocol;
  IObjectPool			*_pool;
  std::list<std::pair<Trame *, bool> >	*_list;
  Mutex				*_mutex;
  bool				_quit;
public:
  CodeBreaker();
  virtual ~CodeBreaker();
  void				run();
  void				setQuit(bool const quit);
private:
  void				getNewObject();
  bool				newCode(std::string const &str);
  bool				newCode(Trame *trame);
  void				execCode();
  void				initProtocol();
};

void				*runCodeBreaker(void *data);

#endif
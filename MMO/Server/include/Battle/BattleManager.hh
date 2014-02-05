//
// BattleManager.hh for BattleManager in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 11:51:11 2014 antoine maitre
// Last update Wed Feb  5 12:22:19 2014 antoine maitre
//

#ifndef				__BATTLEMANAGER_HH__
# define			__BATTLEMANAGER_HH__

# include			"Utility/Singleton.hpp"
# include			"BattleUpdater.hh"

class				BattleManager : public Thread
{
private:
  bool                          _quit;
  Mutex                         *_mutex;
  std::list<BattleUpdater *>	_battleUpdaters;
public:
  BattleManager();
  virtual ~BattleManager();
  
  bool				spell(Trame *);
  bool				capture(Trame *);
  bool				dswitch(Trame *);
};
#endif


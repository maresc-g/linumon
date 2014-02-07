//
// BattleManager.hh for BattleManager in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 11:51:11 2014 antoine maitre
// Last update Fri Feb  7 11:18:10 2014 alexis mestag
//

#ifndef				__BATTLEMANAGER_HH__
# define			__BATTLEMANAGER_HH__

# include			"Utility/Singleton.hpp"
# include			"BattleUpdater.hh"

class				BattleManager : public Singleton<BattleManager>
{
  friend class			Singleton<BattleManager>;

private:
  Mutex                         *_mutex;
  std::list<BattleUpdater *>	_battleUpdaters;

private:
  BattleManager();
  virtual ~BattleManager();

  void				deleteBattleUpdaters();

public:
  bool				spell(Trame *);
  bool				capture(Trame *);
  bool				dswitch(Trame *);
};

#endif

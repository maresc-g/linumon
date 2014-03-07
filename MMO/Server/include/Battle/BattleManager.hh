//
// BattleManager.hh for BattleManager in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 11:51:11 2014 antoine maitre
// Last update Fri Mar  7 14:22:40 2014 antoine maitre
//

#ifndef				__BATTLEMANAGER_HH__
# define			__BATTLEMANAGER_HH__

# include			"Utility/Singleton.hpp"
# include			"BattleUpdater.hh"

class				BattleManager : public Singleton<BattleManager>
{
  friend class			Singleton<BattleManager>;
  unsigned int			_id;

private:
  Mutex                         *_mutex;
  std::list<BattleUpdater *>	_battleUpdaters;

private:
  BattleManager();
  virtual ~BattleManager();

  void				deleteBattleUpdaters();

public:
  void				newBattle(Player *player1, Player *player2);
  bool				spell(Trame *);
  bool				capture(Trame *);
  bool				dswitch(Trame *);
  bool				inBattle(Player *player);
  void				disconnect(unsigned int const idPlayer);
};

#endif

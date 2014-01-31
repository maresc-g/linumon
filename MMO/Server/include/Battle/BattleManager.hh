//
// BattleManager.hh for BattleManager in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 11:51:11 2014 antoine maitre
// Last update Wed Jan 29 15:17:44 2014 antoine maitre
//

#ifndef				__BATTLEMANAGER_HH__
# define			__BATTLEMANAGER_HH__

# include			"Utility/Singleton.hpp"

class				BattleManager : public Singleton<BattleManager>
{
public:
  BattleManager();
  virtual ~BattleManager();
};
#endif

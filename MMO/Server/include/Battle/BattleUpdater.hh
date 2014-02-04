//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Mon Feb  3 15:37:15 2014 antoine maitre
//

#ifndef					__BATTLEUPDATER_HH__
# define				__BATTLEUPDATER_HH__

# include				<tuple>
# include				<utility>
# include				<list>
# include				"Battle/Battle.hh"
# include				"Thread/Thread.hpp"
# include				"Trame/Trame.hh"
# include				"Entities/Spell.hh"

# define				DEFAULT_STORAGE_BATTLE	100

class					BattleUpdater : public Thread
{
public:
  BattleUpdater();
  virtual ~BattleUpdater();
  std::list<Battle *>			*_battles;
  bool					newBattle(Player*, Player*);
  bool					spell(Trame *);
  bool					capture(Trame *);
  bool					dswitch(Trame *);
};

#endif

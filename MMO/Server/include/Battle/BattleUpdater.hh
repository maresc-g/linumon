//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Tue Feb  4 17:34:07 2014 antoine maitre
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

class					BattleUpdater : public Thread
{
private:
  bool                          _quit;
  Mutex                         *_mutex;
  std::list<Trame *>		_trames;
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

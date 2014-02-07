//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Fri Feb  7 11:22:33 2014 alexis mestag
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
# include				"Utility/GenericSerialization.hpp"

class					BattleUpdater : public Thread
{
private:
  bool					_quit;
  Mutex		                        *_mutex;
  std::list<Trame *>			_trames;
  std::list<Battle *>			*_battles;

public:
  BattleUpdater();
  virtual ~BattleUpdater();
  bool					newBattle(Player*, Player*);
  bool					spell(Trame *);
  bool					capture(Trame *);
  bool					dswitch(Trame *);
};

#endif

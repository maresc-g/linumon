//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Fri Feb  7 12:23:29 2014 alexis mestag
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

typedef std::function <bool (Trame *)> funcBattle;

class					BattleUpdater : public Thread
{
private:
  bool					_quit;
  Mutex		                        *_mutex;
  std::list<Trame *>			_trames;
  std::list<Battle *>			*_battles;
  std::map<std::string, funcBattle>     *_funcs;

public:
  BattleUpdater();
  virtual ~BattleUpdater();
  void					lock();
  void					unlock();
  void					launch();
  bool					newBattle(Player *player1, Player *player2);
  bool					spell(Trame *);
  bool					capture(Trame *);
  bool					dswitch(Trame *);
  void					addTrame(Trame );
};

#endif

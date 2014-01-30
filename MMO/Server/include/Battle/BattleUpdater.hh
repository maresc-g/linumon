//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Thu Jan 30 14:12:31 2014 antoine maitre
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
private:
  std::list<std::pair<bool, Trame *> >	*_msg;
public:
  BattleUpdater();
  virtual ~BattleUpdater();
  std::list<Battle *>			*_battles;
  bool					launchBattle(Player *, Player *);
  bool					spell(Trame *trame);
  bool					spellEffect(Trame *trame);
  bool					capture(Trame *trame);
  bool					captureEffect(Trame *trame);
  bool					datSwitch(Trame *trame);
  bool					deadMob(Trame *trame);
  bool					endBattle(Trame *trame);
};

#endif

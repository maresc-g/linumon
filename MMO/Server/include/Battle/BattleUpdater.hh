//
// BattleUpdater.hh for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:25:25 2014 antoine maitre
// Last update Sun Mar  9 00:18:38 2014 laurent ansel
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

#define	DEFAULT_STORAGE_BATTLE		100

class					BattleUpdater;

typedef std::function <bool (Trame *)> funcBattle;

class					BattleUpdater : public Thread
{
private:
  bool					_quit;
  Mutex		                        *_mutex;
  std::list<std::pair<Trame *, bool> >	*_trames;
  std::list<Battle *>			*_battles;
  std::map<std::string, funcBattle>     *_funcs;
  unsigned int				_nbTrame;

public:
  BattleUpdater();
  virtual ~BattleUpdater();
  void					lock();
  void					unlock();
  void					run();
  bool					newBattle(Player *player1, Player *player2, unsigned int const id);
  bool					spell(Trame *);
  bool					capture(Trame *);
  bool					dswitch(Trame *);
  void					addTrame(Trame &);
  int					getNumOfBattle() const;
  std::list<Battle *>			&getBattles() const;
  void					disconnect(unsigned int const idPlayer);
  void					setQuit(bool const quit);
};

void					*launch(void *data);

#endif

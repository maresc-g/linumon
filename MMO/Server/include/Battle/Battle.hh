//
// Battle.hh for battle in /home/maitre_c/work/linumon/MMO/Common/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Tue Jan 28 15:37:45 2014 antoine maitre
// Last update Thu Mar 13 14:31:27 2014 antoine maitre
//

#ifndef				__BATTLE_HH__
# define			__BATTLE_HH__

# include			<string>
# include			<tuple>
# include			"AI/AI.hh"
# include			"Entities/Player.hh"
# include			"Server/Server.hh"

class				Battle 
{
public:
  enum				eBattle
    {
      PVE,
      PVP
    };
private:
  unsigned int const		_id;
  eBattle const			_type;
  unsigned int const		_mobNumber;
  std::list<Mob *>		_mobs;
  std::list<Player *>		_players;
  int				_money;
  int				_exp;
  unsigned int			_idLooser;
  bool				_success;
public:
  Battle(unsigned int const id, eBattle const type, unsigned int const mobNumber, Player *player1, Player *player2);
  ~Battle();
  unsigned int			getID() const;
  void				replace();
  eBattle 			getType() const;
  bool				dswitch(unsigned int const, unsigned int const);
  bool				capture(unsigned int const);
  bool				spell(unsigned int const, unsigned int const, Spell *);
  bool				checkEnd();
  bool				isInThisBattle(unsigned int const idPlayer);
  void				setSuccess(bool const val);
  void				trameSpell(unsigned int const idPlayer, Spell const *spell, unsigned int const launcher, unsigned int const target) const;
  void				trameSwitch(unsigned int const idPlayer, unsigned int const target, unsigned int const newMob) const;
  void				trameSpellEffect(unsigned int const idPlayer, unsigned int const target, int const hpChange) const;
  void				trameDeadMob(unsigned int const idPlayer, unsigned int const idMob) const;
  void				trameCapture(unsigned int const idPlayer, unsigned int const idMob) const;
  void				trameLaunchBattle(unsigned int const idPlayer, Player *player) const;
  void				trameTurnTo(unsigned int const idPlayer, unsigned int const idMob) const;
  void				trameEndBattle();
  void				next();
};

bool				compareSpeed(Mob *, Mob *);

#endif

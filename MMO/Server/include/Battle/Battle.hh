//
// Battle.hh for battle in /home/maitre_c/work/linumon/MMO/Common/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Tue Jan 28 15:37:45 2014 antoine maitre
// Last update Wed Mar 26 11:32:40 2014 antoine maitre
//

#ifndef				__BATTLE_HH__
# define			__BATTLE_HH__

# include			<string>
# include			<tuple>
# include			"Entities/Mob.hh"
# include			"Battle/BattleParams.hh"

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
  unsigned int			_idLooser;
  bool				_success;
  BattleParams			*_battleParams;

public:
  Battle(unsigned int const id, eBattle const type, unsigned int const mobNumber, Player *player1, Player *player2);
  virtual ~Battle();
  unsigned int			getID() const;
  void				replace();
  eBattle 			getType() const;
  bool				dswitch(unsigned int const, unsigned int const);
  bool				capture(unsigned int const);
  bool				spell();
  bool				checkEnd();
  bool				isInThisBattle(unsigned int const idPlayer);
  void				setSuccess(bool const val);
  void				disconnect(unsigned int const idPlayer);
  void				trameSpell(unsigned int const idPlayer, Spell const *spell, unsigned int const launcher, unsigned int const target) const;
  void				trameSwitch(unsigned int const idPlayer, unsigned int const target, unsigned int const newMob, unsigned int const player) const;
  void				trameSpellEffect(unsigned int const idPlayer, unsigned int const target, int const hpChange) const;
  void				trameDeadMob(unsigned int const idPlayer, unsigned int const idMob) const;
  void				trameCapture(unsigned int const idPlayer, Mob const *, bool const success) const;
  void				trameLaunchBattle(unsigned int const idPlayer, Player *player) const;
  void				trameTurnTo(unsigned int const idPlayer, unsigned int const idMob) const;
  void				trameEndBattle();
  void				next();

  Mob				*getMobById(unsigned int const id);
  Mob				*getLauncherMob();
  void				setLauncherMob(Mob *mob);
  Mob				*getTargetMob();
  void				setTargetMob(Mob *mob);
  Spell				*getSpell();
  void				setSpell(Spell *);
};

bool				compareSpeed(Mob *, Mob *);

#endif

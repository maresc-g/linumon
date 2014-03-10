//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Mon Mar 10 01:06:04 2014 alexis mestag
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Utility/ISerialization.hh"

class			Player;
class			MobModel;
class			Type;

class			Mob : public Persistent, public ACharacter, public ISerialization
{
  friend class		odb::access;

private:
  Player const		*_player;
  MobModel const	*_model;
  Stats			*_currentStats;
  bool			_inBattle;

private:
  Mob();

  void			setModel(MobModel const &model);

  Stats const		&getCurrentStats() const;
  void			setCurrentStats(Stats const &stats);

  void			setInBattle(bool const inBattle);

public:
  Mob(Mob const &rhs);
  Mob(MobModel const &model, Level::type const level);
  virtual ~Mob();

  Mob			&operator=(Mob const &rhs);

  Player const		*getPlayer() const;
  void			setPlayer(Player const *player);

  MobModel const	&getModel() const;
  Type const		&getType() const;

  /*
  ** Mob special stats management (Max and Current)
  */
  Stats			getMaxStats() const;
  Stat::value_type	getMaxStat(std::string const &key) const;
  Stat::value_type	getCurrentStat(std::string const &key) const;
  bool			setCurrentStat(std::string const &key, Stat::value_type const value);

  /*
  ** Battle state management
  */
  bool			isInBattle() const;
  void			enterBattle();
  void			leaveBattle();

  /*
  ** Tests methods
  */
  void			displayMaxStats() const;
  void			displayCurrentStats() const;

  virtual bool		serialization(Trame &trame) const;
  static Mob		*deserialization(Trame const &trame);
};

# include		"Entities/Player.hh"
# include		"Entities/MobModel.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Mob)
#  pragma db member(Mob::_currentStats) transient
#  pragma db member(Mob::_inBattle) transient
#  pragma db member(Mob::_model) not_null column("model_id")
#  pragma db member(Mob::_player) inverse(mobs)
#  pragma db member(Mob::currentStats) virtual(Stats::container_type) get(_currentStats->getContainer()) set(_currentStats->setContainer(?))
# endif

#endif

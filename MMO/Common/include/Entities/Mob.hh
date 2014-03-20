//
// Mob.hh for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:37:13 2013 alexis mestag
// Last update Thu Mar 20 14:00:45 2014 alexis mestag
//

#ifndef			__MOB_HH__
# define		__MOB_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"
# include		"Utility/ISerialization.hh"

class			Player;
class			MobModel;
class			Carcass;
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
  void			setCurrentStats(Stats const &stats);

public:
  Mob(Mob const &rhs);
  Mob(MobModel const &model, Levelable::type const level, Player const *player = NULL);
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

  Stats const		&getRawCurrentStats() const;
  Stats			getCurrentStats() const;
  Stat::value_type	getCurrentStat(std::string const &key) const;
  bool			setCurrentStat(std::string const &key, Stat::value_type const value);
  bool			incCurrentStat(std::string const &key, Stat::value_type const inc);
  bool			decCurrentStat(std::string const &key, Stat::value_type const dec);

  /*
  ** Mob's Carcass
  */
  Carcass		*getNewCarcass() const;

  /*
  ** Mobs'ExperienceCurve
  */
#ifndef		CLIENT_COMPILATION
  virtual ExperienceCurve const	&getExperienceCurve() const;
#endif

  unsigned int		getExpSeed() const;
  Levelable::type	getGivenExp() const;

  unsigned int		getCatchRate() const;

  /*
  ** Battle state management
  */
  virtual void			enterBattle();
  virtual void			leaveBattle();

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
#  pragma db member(Mob::name) virtual(std::string) get(getName()) set(setName(?)) type("VARCHAR(24)")
#  pragma db member(Mob::_model) not_null
#  pragma db member(Mob::_player) inverse(mobs)
#  pragma db member(Mob::currentStats) virtual(Stats::container_type) get(_currentStats->getContainer()) set(_currentStats->setContainer(?))
# endif

#endif

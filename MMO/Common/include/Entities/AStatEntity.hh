//
// AStatEntity.hh for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:21:41 2013 alexis mestag
// Last update Fri Mar  7 13:11:00 2014 laurent ansel
//

#ifndef			__ASTATENTITY_HH__
# define		__ASTATENTITY_HH__

# include		"Entities/AEntity.hh"
# include		"Stats/Stats.hh"

class			AStatEntity : public AEntity
{
  friend class		odb::access;

public:
  typedef enum		eStatEntity
    {
      NONE,
      CHARACTER,
      MOBMODEL
    }			eStatEntity;

private:
  eStatEntity			_statEntityType;
  AuthorizedStatKeys const	*_authKeys;
  Stats				*_stats;
  Stats				*_tmpStats;
  bool				_inBattle;

protected:
  AStatEntity();
  AStatEntity(std::string const &name, eStatEntity const statEntityType);
  AStatEntity(AStatEntity const &rhs);

  AStatEntity		&operator=(AStatEntity const &rhs);

  void			setStatEntityType(eStatEntity const statEntityType);

  Stat::value_type	getStat(StatKey const &key) const;
  bool			setStat(StatKey const &key, Stat::value_type const value,
				bool const add = false);
  Stat::value_type	getTmpStat(StatKey const &key) const;
  bool			setTmpStat(StatKey const &key, Stat::value_type const value,
				   bool const add = false);

  void			initTmpStats();
  void			endTmpStats();

  void			setInBattle(bool const inBattle);

public:
  virtual ~AStatEntity();

  eStatEntity		getStatEntityType() const;

  Stats const		&getStats() const;
  void			setStats(Stats const &stats);
  Stats const		&getTmpStats() const;
  void			setTmpStats(Stats const &stats);

  AuthorizedStatKeys const	&getStatKeys() const;
  void				setStatKeys(AuthorizedStatKeys const &keys);
  bool				isKeyAuthorized(StatKey const &key) const;
  StatKey const			*getKey(std::string const &key) const;

  Stat::value_type	getStat(std::string const &key) const;
  bool			setStat(std::string const &key, Stat::value_type const value,
				bool const add = false);
  Stat::value_type	getTmpStat(std::string const &key) const;
  bool			setTmpStat(std::string const &key, Stat::value_type const value,
				   bool const add = false);

  bool			isInBattle() const;
  void			enterBattle();
  void			leaveBattle();

  void			displayTmpStats() const;
};

# ifdef	ODB_COMPILER
#  pragma db object(AStatEntity) abstract
#  pragma db member(AStatEntity::_statEntityType) transient
#  pragma db member(AStatEntity::_stats) transient
#  pragma db member(AStatEntity::_tmpStats) transient
#  pragma db member(AStatEntity::_inBattle) transient
#  pragma db member(AStatEntity::stats) virtual(Stats::container_type) get(_stats->getContainer()) set(_stats->setContainer(?))
#  pragma db member(AStatEntity::tmpStats) virtual(Stats::container_type) get(_tmpStats->getContainer()) set(_tmpStats->setContainer(?))
# endif

#endif

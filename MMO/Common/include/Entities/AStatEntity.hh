//
// AStatEntity.hh for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:21:41 2013 alexis mestag
// Last update Sun Mar 23 14:22:03 2014 alexis mestag
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

protected:
  AStatEntity();
  AStatEntity(std::string const &name, eStatEntity const statEntityType);
  AStatEntity(AStatEntity const &rhs);

  AStatEntity		&operator=(AStatEntity const &rhs);

  void			setStatEntityType(eStatEntity const statEntityType);

public:
  virtual ~AStatEntity();

  eStatEntity		getStatEntityType() const;

  /*
  ** Authorized keys management
  ** It's not possible to add a stat with a key which is not in this container
  ** To get the value of such a key won't raise an exception but will return Stat::value_type()
  */
  AuthorizedStatKeys const	&getAuthorizedStatKeys() const;
  void				setAuthorizedStatKeys(AuthorizedStatKeys const &keys);
  StatKey const			*getKey(std::string const &key) const;

  /*
  ** Simple stats management
  **   => sets the whole container
  ** These stats are affected by the stuff the Entity wears
  */
  Stats const		&getStats() const;
  void			setStats(Stats const &stats);

  /*
  ** Gets the value of a given stat by the key
  ** Returns Stat::value_type() if the key isn't found
  */
  Stat::value_type	getStat(std::string const &key) const;
  bool			setStat(std::string const &key, Stat::value_type const value);
  bool			incStat(std::string const &key, Stat::value_type const inc);
  bool			decStat(std::string const &key, Stat::value_type const dec);

  Stat::bonus_type	getBonus(std::string const &key) const;
  bool			setBonus(std::string const &key, Stat::bonus_type const value);
  bool			incBonus(std::string const &key, Stat::bonus_type const inc);
  bool			decBonus(std::string const &key, Stat::bonus_type const dec);
};

# ifdef	ODB_COMPILER
#  pragma db object(AStatEntity) abstract
#  pragma db member(AStatEntity::_statEntityType) transient
#  pragma db member(AStatEntity::_stats) transient
#  pragma db member(AStatEntity::_authKeys) not_null
#  pragma db member(AStatEntity::stats) virtual(Stats::container_type) get(_stats->getContainer()) set(_stats->setContainer(?)) value_column("") unordered
# endif

#endif

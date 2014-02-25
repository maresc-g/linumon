//
// Stats.hh for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:58:39 2013 alexis mestag
// Last update Tue Feb 25 15:59:07 2014 alexis mestag
//

#ifndef				__STATS_HH__
# define			__STATS_HH__

# include			<odb/core.hxx>
# include			<list>
# include			"Stats/Stat.hh"
# include			"Utility/ISerialization.hh"
# include			"Stats/AuthorizedStatKeys.hh"
# include			"Stats/StatKey.hh"

class				Stats
{
  friend class			odb::access;

public:
  typedef std::list<Stat *>	container_type;

private:
  AuthorizedStatKeys const	*_authKeys;
  container_type		_stats;

private:
  container_type		&getStatsDeepCopy() const;
  void				deleteStats();

public:
  Stats();
  Stats(Stats const &rhs);
  virtual ~Stats();

  Stats				&operator=(Stats const &rhs);
  Stat::value_type		operator[](StatKey const &key) const;
  Stat::value_type		operator[](std::string const &key) const;

  // Do not assign if !Stat.isShortLived()
  void				smartAssign(Stats const &rhs);

  void				setStats(container_type &stats);
  container_type const		&getStats() const;

  AuthorizedStatKeys const	&getKeys() const;
  void				setKeys(AuthorizedStatKeys const &keys);

  Stat::value_type		getStat(StatKey const &key) const;
  Stat::value_type		getStat(std::string const &key) const;

  void				setStat(StatKey const &key, Stat::value_type const value);
  void				setStat(std::string const &key, Stat::value_type const value);

  virtual bool			serialization(Trame &trame) const;
  static Stats			*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Stats)
# endif

#endif

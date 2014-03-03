//
// Stats.hh for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:58:39 2013 alexis mestag
// Last update Mon Mar  3 12:19:50 2014 alexis mestag
//

#ifndef				__STATS_HH__
# define			__STATS_HH__

# include			<odb/core.hxx>
# include			<list>
# include			"Stats/Stat.hh"
# include			"Utility/ISerialization.hh"
# include			"Stats/AuthorizedStatKeys.hh"
# include			"Stats/StatKey.hh"
# include			"Utility/Wrapper.hpp"

class				Stats : public ContainerWrapper<std::list<Stat *>>
{
  friend class			odb::access;

private:
  container_type		_stats;

private:
  container_type		&getStatsDeepCopy() const;
  void				deleteStats();

public:
  Stats();
  Stats(Stats const &rhs);
  virtual ~Stats();

  Stats				&operator=(Stats const &rhs);
  Stats				&operator+=(Stats const &rhs);
  Stats				&operator-=(Stats const &rhs);
  void				add(Stats const &rhs);
  void				sub(Stats const &rhs);
  // Stats				operator+(Stats const &rhs) const;
  // Stats				operator-(Stats const &rhs) const;

  Stat::value_type		operator[](StatKey const &key) const;
  Stat::value_type		operator[](std::string const &key) const;

  Stat				*get(StatKey const &key) const;
  Stat				*get(std::string const &key) const;

  // Do not assign if !Stat.isShortLived() sauf s'il n'y est pas
  void				smartAssign(Stats const &rhs);
  void				removeShortLivedStats();

  void				setStats(container_type const &stats);
  container_type const		&getStats() const;

  Stat::value_type		getStat(StatKey const &key) const;
  Stat::value_type		getStat(std::string const &key) const;

  void				setStat(StatKey const &key, Stat::value_type const value,
					bool const add = false);
  // This one below should not be called
  // void				setStat(std::string const &key, Stat::value_type const value,
  // 					bool const add = false);

  virtual bool			serialization(Trame &trame) const;
  static Stats			*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Stats)
# endif

#endif

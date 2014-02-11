//
// Stats.hh for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:58:39 2013 alexis mestag
// Last update Tue Feb 11 14:41:20 2014 antoine maitre
//

#ifndef			__STATS_HH__
# define		__STATS_HH__

# include		<odb/core.hxx>
# include		<list>
# include		"Stats/Stat.hh"
# include		"Utility/ISerialization.hh"

class			Stats
{
  friend class		odb::access;

private:
  std::list<Stat *>	_stats;

private:
  std::list<Stat *>	&getStatsDeepCopy() const;
  void			deleteStats();

public:
  Stats();
  Stats(Stats const &rhs);
  virtual ~Stats();

  Stats			&operator=(Stats const &rhs);
  void			setStats(std::list<Stat *> &stats);
  void			setStat(Stat::eStat const stat, int const value);
  int			getStat(Stat::eStat const stat) const;
  virtual bool		serialization(Trame &trame) const;
  static Stats		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Stats)
# endif

#endif

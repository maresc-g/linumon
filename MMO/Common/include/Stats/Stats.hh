//
// Stats.hh for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:58:39 2013 alexis mestag
// Last update Tue Dec  3 13:14:31 2013 alexis mestag
//

#ifndef			__STATS_HH__
# define		__STATS_HH__

# include		<list>
# include		"Stats/Stat.hh"

class			Stats
{
private:
  std::list<Stat *>	*_stats;

private:
  std::list<Stat *>	*getStatsDeepCopy() const;
  void			setStats(std::list<Stat *> *const stats);
  void			deleteStats();

public:
  Stats();
  Stats(Stats const &rhs);
  virtual ~Stats();

  Stats			&operator=(Stats const &rhs);
};

#endif

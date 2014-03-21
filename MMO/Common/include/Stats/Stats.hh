//
// Stats.hh for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:58:39 2013 alexis mestag
// Last update Thu Mar 20 22:59:01 2014 alexis mestag
//

#ifndef				__STATS_HH__
# define			__STATS_HH__

# include			<list>
# include			"Stats/AuthorizedStatKeys.hh"
# include			"Stats/Stat.hh"
# include			"Stats/StatKey.hh"
# include			"Utility/ISerialization.hh"
# include			"Utility/Wrapper.hpp"

class				Stats : public ContainerWrapper<std::list<Stat>>
{
private:
  container_type const		&getStats() const;
  void				setStats(container_type const &c);

  void				add(Stats const &rhs);
  void				sub(Stats const &rhs);

  Stat				*get(StatKey const &key);

public:
  Stats();
  Stats(Stats const &rhs);
  virtual ~Stats();

  Stats				&operator=(Stats const &rhs);
  Stats				&operator+=(Stats const &rhs);
  Stats				&operator-=(Stats const &rhs);
  Stats				operator+(Stats const &rhs) const;
  Stats				operator-(Stats const &rhs) const;

  Stat::value_type		operator[](StatKey const &key) const;

  Stat const			*get(StatKey const &key) const;

  void				resetShortLivedStats(Stats const &rhs);
  void				removeShortLivedStats();

  Stat::value_type		getStat(StatKey const &key) const;
  void				setStat(StatKey const &key, Stat::value_type const value);

  virtual bool			serialization(Trame &trame) const;
  static Stats			*deserialization(Trame const &trame);
};

#endif

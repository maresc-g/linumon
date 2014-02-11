//
// Stats.cpp for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 22:02:08 2013 alexis mestag
// Last update Tue Feb 11 14:40:57 2014 antoine maitre
//

#include			<sstream>
#include			<functional>
#include			"Stats/Stats.hh"

Stats::Stats()
{

}

Stats::Stats(Stats const &rhs)
{
  *this = rhs;
}

Stats::~Stats()
{
  this->deleteStats();
}

Stats				&Stats::operator=(Stats const &rhs)
{
  if (this != &rhs)
    {
      this->setStats(rhs.getStatsDeepCopy());
    }
  return (*this);
}

std::list<Stat *>		&Stats::getStatsDeepCopy() const
{
  std::list<Stat *>		*ret = new std::list<Stat *>;

  for (auto it = _stats.cbegin() ; it != _stats.cend() ; ++it)
    {
      ret->push_back(new Stat(**it));
    }
  return (*ret);
}

void				Stats::setStats(std::list<Stat *> &stats)
{
  this->deleteStats();
  _stats = stats;
}

int				Stats::getStat(Stat::eStat stat) const
{
  for (auto it = this->_stats.begin(); it != this->_stats.end(); it++)
    if ((*it)->getStatType() == stat)
      return ((*it)->getValue());
  return (-1);
}

void				Stats::setStat(Stat::eStat stat, int const value)
{
  for (auto it = this->_stats.begin(); it != this->_stats.end(); it++)
    if ((*it)->getStatType() == stat)
      (*it)->setValue(value);
}

void				Stats::deleteStats()
{
  static std::function<bool(Stat *)> f = [](Stat *stat) -> bool {
    delete stat;
    return (true);
  };

  _stats.remove_if(f);
}

bool				Stats::serialization(Trame &trame) const
{
  bool				ret = true;

  for (auto it = this->_stats.begin() ; it != this->_stats.end() ; ++it)
    {
      (*it)->serialization(trame);
    }
  return (ret);
}

Stats				*Stats::deserialization(Trame const &trame)
{
  Stats				*stats = NULL;
  std::ostringstream		str;
  std::list<Stat *>		*stat;
  auto				members = trame.getMemberNames();

  stats = new Stats;
  stat = new std::list<Stat *>;
  for (auto it = members.begin() ; it != members.end() ; ++it)
    stat->push_back(Stat::deserialization(trame(trame[*it])));
  stats->setStats(*stat);
  return (stats);
}

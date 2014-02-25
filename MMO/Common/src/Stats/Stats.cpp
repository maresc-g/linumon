//
// Stats.cpp for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 22:02:08 2013 alexis mestag
// Last update Tue Feb 25 15:59:35 2014 alexis mestag
//

#include			<sstream>
#include			<functional>
#include			<algorithm>
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
      this->setKeys(rhs.getKeys());
    }
  return (*this);
}

Stat::value_type		Stats::operator[](StatKey const &key) const
{
  static std::function<bool(Stat *)>	statSeeker = [&](Stat *s) -> bool {
    return (s->getKey() == key);
  };
  Stat::value_type			ret = Stat::value_type();

  if (_authKeys->isAuthorized(key))
    {
      auto			it = std::find_if(_stats.begin(), _stats.end(), statSeeker);

      if (it != _stats.end())
	ret = (*it)->getValue();
    }
  return (ret);
}

Stat::value_type		Stats::operator[](std::string const &key) const
{
  return ((*this)[StatKey(key)]);
}

Stats::container_type		&Stats::getStatsDeepCopy() const
{
  std::list<Stat *>		*ret = new std::list<Stat *>;

  for (auto it = _stats.cbegin() ; it != _stats.cend() ; ++it)
    {
      ret->push_back(new Stat(**it));
    }
  return (*ret);
}

void				Stats::smartAssign(Stats const &rhs)
{
  this->setKeys(rhs.getKeys());
  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it)
    {
      if ((*it)->isShortLived())
	this->setStat((*it)->getKey(), (*it)->getValue());
    }
}

void				Stats::setStats(container_type &stats)
{
  this->deleteStats();
  _stats = stats;
}

Stats::container_type const	&Stats::getStats() const
{
  return (_stats);
}

AuthorizedStatKeys const	&Stats::getKeys() const
{
  return (*_authKeys);
}

void				Stats::setKeys(AuthorizedStatKeys const &keys)
{
  static std::function<bool(Stat *)>	statRemover = [&](Stat *s) -> bool {
    if (keys.isAuthorized(s->getKey()))
      return (false);
    return (true);
  };

  _authKeys = &keys;
  _stats.remove_if(statRemover);
}

Stat::value_type		Stats::getStat(StatKey const &key) const
{
  for (auto it = this->_stats.begin(); it != this->_stats.end(); it++)
    if ((*it)->getKey() == key)
      return ((*it)->getValue());
  return (-1);
}

Stat::value_type		Stats::getStat(std::string const &key) const
{
  return (this->getStat(StatKey(key)));
}

void				Stats::setStat(StatKey const &key, Stat::value_type const value)
{
  for (auto it = this->_stats.begin(); it != this->_stats.end(); it++)
    if ((*it)->getKey() == key)
      (*it)->setValue(value);
}

void				Stats::setStat(std::string const &key, Stat::value_type const value)
{
  this->setStat(StatKey(key), value);
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
  std::list<Stat *>		*stat;
  Stat				*st;

  if (trame.isMember("STATS"))
    {
      auto				members = trame["STATS"].getMemberNames();

      stats = new Stats;
      stat = new std::list<Stat *>;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  st = Stat::deserialization(trame(trame["STATS"][*it]));
	  if (st)
	    stat->push_back(st);
	}
      stats->setStats(*stat);
    }
  else if (trame.isMember("TMPSTATS"))
    {
      auto				members = trame["TMPSTATS"].getMemberNames();

      stats = new Stats;
      stat = new std::list<Stat *>;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  st = Stat::deserialization(trame(trame["TMPSTATS"][*it]));
	  if (st)
	    stat->push_back(st);
	}
      stats->setStats(*stat);
    }
  return (stats);
}

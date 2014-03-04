//
// Stats.cpp for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 22:02:08 2013 alexis mestag
// Last update Mon Mar  3 14:26:04 2014 alexis mestag
//

#include			<sstream>
#include			<functional>
#include			<algorithm>
#include			"Stats/Stats.hh"

Stats::Stats() :
  ContainerWrapper<container_type>()
{

}

Stats::Stats(Stats const &rhs) :
  ContainerWrapper<container_type>()
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
      // this->setStats(rhs.getStatsDeepCopy());
      this->setStats(rhs.getStats());
    }
  return (*this);
}

Stat::value_type		Stats::operator[](StatKey const &key) const
{
  return (this->getStat(key));
}

Stat::value_type		Stats::operator[](std::string const &key) const
{
  return (this->getStat(key));
}

void				Stats::add(Stats const &rhs)
{
  Stat const			*rhsStat;
  Stat				*stat;

  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it) {
    rhsStat = *it;
    stat = this->get(rhsStat->getKey());
    if (stat)
      *stat += *rhsStat;
    else
      this->setStat(rhsStat->getKey(), rhsStat->getValue(), true);
  }
}

Stats				&Stats::operator+=(Stats const &rhs)
{
  this->add(rhs);
  return (*this);
}

void				Stats::sub(Stats const &rhs)
{
  Stat const			*rhsStat;
  Stat				*stat;

  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it) {
    rhsStat = *it;
    stat = this->get(rhsStat->getKey());
    if (stat) {
      *stat -= *rhsStat;
    }
    // Nothing to do if the key's not found
  }
}

Stats				&Stats::operator-=(Stats const &rhs)
{
  this->sub(rhs);
  return (*this);
}

Stat				*Stats::get(StatKey const &key) const
{
  return (this->get(key.getName()));
}

Stat				*Stats::get(std::string const &key) const
{
  /*
  ** Warning :	the std::function below cannot be static, remember it !
  **		It would be instanciated only ONE time so
  **		it would screw up the comparison with the key parameter
  */
  std::function<bool(Stat *)>	statSeeker = [&](Stat *s) -> bool {
    return (s->getKey().getName() == key);
  };
  auto				it = std::find_if(this->begin(), this->end(), statSeeker);

  return (it != this->end() ? *it : NULL);  
}

void				Stats::smartAssign(Stats const &rhs)
{
  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it)
    {
      if ((*it)->isShortLived() || !this->get((*it)->getKey())) {
	this->setStat((*it)->getKey(), (*it)->getValue(), true);
      }
    }
}

void				Stats::removeShortLivedStats()
{
  static std::function<bool(Stat *)>	shortLivedStatSeeker = [](Stat *s) -> bool {
    if (s->isShortLived()) {
      delete s;
      return (true);
    }
    return (false);
  };

  this->getContainer().remove_if(shortLivedStatSeeker);
}

void				Stats::setStats(container_type const &stats)
{
  Stat const			*rhsStat;
  Stat				*stat;

  for (auto it = stats.begin() ; it != stats.end() ; ++it) {
    rhsStat = *it;
    stat = this->get(rhsStat->getKey());
    if (stat)
      *stat = *rhsStat;
    else
      this->setStat(rhsStat->getKey(), rhsStat->getValue(), true);
  }
}

Stats::container_type const	&Stats::getStats() const
{
  return (this->getContainer());
}

Stat::value_type		Stats::getStat(StatKey const &key) const
{
  return (this->getStat(key.getName()));
}

Stat::value_type		Stats::getStat(std::string const &key) const
{
  Stat				*s = this->get(key);

  return (s ? s->getValue() : Stat::value_type());
}

void				Stats::setStat(StatKey const &key, Stat::value_type const value,
					       bool const add)
{
  Stat				*s = this->get(key);

  if (s)
    s->setValue(value);
  else if (add) {
    this->getContainer().push_back(new Stat(key, value));
  }
}

/*
** These 2 functions (above and below) are " duplicated " for persisting issues
** The one above is very useful for the Stats::smartAssign method (for the server ONLY)
** In fact, the one below should not be called at all
*/

// void				Stats::setStat(std::string const &key, Stat::value_type const value,
// 					       bool const add)
// {
//   Stat				*s = this->get(key);

//   if (s)
//     s->setValue(value);
//   else if (add)
//     _stats.push_back(new Stat(StatKey(key), value));
//   std::cout << "WARNING FROM MESTAG : Stats::setStat with string key parameter should not be called" << std::endl;
// }

void				Stats::deleteStats()
{
  static std::function<bool(Stat *)> f = [](Stat *stat) -> bool {
    delete stat;
    return (true);
  };

  this->getContainer().remove_if(f);
}

bool				Stats::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;
  unsigned int			nb = 0;

  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      str << nb;
      (*it)->serialization(trame(trame[str.str()]));
      str.str("");
      nb++;
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

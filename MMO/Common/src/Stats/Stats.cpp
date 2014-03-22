//
// Stats.cpp for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 22:02:08 2013 alexis mestag
// Last update Sat Mar 22 18:13:45 2014 alexis mestag
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

}

Stats				&Stats::operator=(Stats const &rhs)
{
  if (this != &rhs)
    {
      this->setStats(rhs.getStats());
    }
  return (*this);
}

Stat::value_type		Stats::operator[](StatKey const &key) const
{
  return (this->getStat(key));
}

Stat				*Stats::get(StatKey const &key)
{
  std::function<bool(Stat)>	statSeeker = [&](Stat s) -> bool {
    return (s.getKey() == key);
  };
  auto				it = std::find_if(this->begin(), this->end(), statSeeker);

  return (it != this->end() ? &*it : NULL);  
}

Stat const			*Stats::get(StatKey const &key) const
{
  std::function<bool(Stat const)>	statSeeker = [&](Stat const s) -> bool {
    return (s.getKey() == key);
  };
  auto				it = std::find_if(this->cbegin(), this->cend(), statSeeker);

  return (it != this->cend() ? &*it : NULL);
}

Stats				&Stats::operator+=(Stats const &rhs)
{
  this->add(rhs);
  return (*this);
}

Stats				&Stats::operator-=(Stats const &rhs)
{
  this->sub(rhs);
  return (*this);
}

Stats				Stats::operator+(Stats const &rhs) const
{
  Stats				ret(*this);

  ret += rhs;
  return (ret);
}

Stats				Stats::operator-(Stats const &rhs) const
{
  Stats				ret(*this);

  ret -= rhs;
  return (ret);
}

void				Stats::add(Stats const &rhs)
{
  Stat const			*rhsStat;
  Stat				*stat;

  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it) {
    rhsStat = &*it;
    stat = this->get(rhsStat->getKey());
    if (stat)
      *stat += *rhsStat;
    else
      this->setStat(rhsStat->getKey(), rhsStat->getValue());
  }
}

void				Stats::sub(Stats const &rhs)
{
  Stat const			*rhsStat;
  Stat				*stat;

  for (auto it = rhs.getStats().begin() ; it != rhs.getStats().end() ; ++it) {
    rhsStat = &*it;
    stat = this->get(rhsStat->getKey());
    if (stat) {
      *stat -= *rhsStat;
    }
  }
}

void				Stats::resetShortLivedStats(Stats const &rhs)
{
  for (auto it = rhs.begin() ; it != rhs.end() ; ++it)
    {
      if (it->isShortLived() || !this->get(it->getKey())) {
	this->setStat(it->getKey(), it->getValue());
      }
    }
}

void				Stats::removeShortLivedStats()
{
  static std::function<bool(Stat)>	shortLivedStatSeeker = [](Stat s) -> bool {
    return (!(s.isShortLived()));
  };

  this->getContainer().remove_if(shortLivedStatSeeker);
}

Stat::value_type		Stats::getStat(StatKey const &key) const
{
  Stat const			*s = this->get(key);

  return (s ? s->getValue() : Stat::value_type());
}

void				Stats::setStat(StatKey const &key, Stat::value_type const value)
{
  Stat				*s = this->get(key);

  if (s)
    s->setRawValue(value);
  else
    this->getContainer().push_back(Stat(key, value));
}

Stats::container_type const	&Stats::getStats() const
{
  return (this->getContainer());
}

void				Stats::setStats(container_type const &rhs)
{
  // std::function<void(Stat const)> statCopier = [&](Stat const s) -> void {
  //   this->getContainer().push_back(s);
  // };

  // std::for_each(rhs.begin(), rhs.end(), statCopier);
  this->setContainer(rhs);
}

bool				Stats::serialization(Trame &trame) const
{
  bool				ret = true;
  // std::ostringstream		str;
  // unsigned int			nb = 0;

  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      //      str << nb;
      it->serialization(trame/*(trame[str.str()])*/);
      // str.str("");
      // nb++;
    }
  return (ret);
}

Stats				*Stats::deserialization(Trame const &trame)
{
  Stats				*stats = NULL;
  std::list<Stat>		stat;
  Stat				*st;

  auto				members = trame.getMemberNames();

  stats = new Stats;
  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      st = Stat::deserialization(trame(trame[*it]));
      if (st)
	{
	  st->setKey(*new StatKey(*it));
	  stat.push_back(*st);
	  delete st;
	}
    }
  stats->setStats(stat);
  return (stats);
}

//
// Stats.cpp for Stats in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 22:02:08 2013 alexis mestag
// Last update Tue Dec  3 13:15:53 2013 alexis mestag
//

#include			<functional>
#include			"Stats/Stats.hh"

Stats::Stats() :
  _stats(new std::list<Stat *>)
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

std::list<Stat *>		*Stats::getStatsDeepCopy() const
{
  std::list<Stat *>		*ret = new std::list<Stat *>;

  for (auto it = _stats->cbegin() ; it != _stats->cend() ; ++it)
    {
      ret->push_back(new Stat(**it));
    }
  return (ret);
}

void				Stats::setStats(std::list<Stat *> *const stats)
{
  this->deleteStats();
  _stats = stats;
}

void				Stats::deleteStats()
{
  static std::function<bool(Stat *)> f = [](Stat *stat) -> bool {
    delete stat;
    return (true);
  };

  _stats->remove_if(f);
  delete _stats;
  _stats = NULL;
}

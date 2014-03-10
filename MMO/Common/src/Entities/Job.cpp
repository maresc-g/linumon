//
// Job.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:04 2014 laurent ansel
// Last update Fri Mar  7 16:32:10 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Job.hh"
#include			"Entities/Stuff.hh"
#include			"Entities/Consumable.hh"

#ifndef			CLIENT_COMPILATION
# include		"Entities/Job-odb.hxx"
# include		"Database/Repositories/Repository.hpp"
#endif

Job::Job():
  Persistent(),
  _currentExp(0),
  _level(new Level),
  _jobModel(NULL)
{
}

Job::~Job()
{
  delete _level;
#ifndef			CLIENT_COMPILATION
  Repository<Job>	*rj = &Database::getRepository<Job>();
  rj->removeFromCache(*this);
#endif
}

Job::Job(Job const &rhs):
  Persistent(rhs), _level(new Level)
{
  *this = rhs;
}

Job				&Job::operator=(Job const &rhs)
{
  if (this != &rhs)
    {
      this->setCurrentExp(rhs.getCurrentExp());
      this->setLevelObject(rhs.getLevelObject());
      this->setJobModel(rhs.getJobModel());
    }
  return (*this);
}

unsigned int			Job::getCurrentExp() const
{
  return (this->_currentExp);
}

void				Job::setCurrentExp(unsigned int const currentExp)
{
  _currentExp = currentExp;
}

Level const			&Job::getLevelObject() const
{
  return (*this->_level);
}

void				Job::setLevelObject(Level const &level)
{
  if (!_level)
    this->_level = new Level(level);
  else
    *this->_level = level;
}

Level::type			Job::getLevel() const
{
  return (_level->getLevel());
}

void				Job::setLevel(Level::type const level)
{
  _level->setLevel(level);
}

Level::type			Job::getExp() const
{
  return (_level->getExp());
}

void				Job::setExp(Level::type const exp)
{
  _level->setExp(exp);
}

JobModel const			&Job::getJobModel() const
{
  return (*this->_jobModel);
}

void				Job::setJobModel(JobModel const &jobModel)
{
  this->_jobModel = &jobModel;
}

bool				Job::doCraft(std::string const &nameCraft, std::list<AItem *> &result, std::list<std::pair<std::string, unsigned int> > &object)
{
  bool				ret = false;
  unsigned int			exp = 0;
  AItem				*item;

  for (auto it = this->getJobModel().getCrafts().begin() ; it != this->getJobModel().getCrafts().end() && !ret; ++it)
    if ((*it)->getName() == nameCraft)
      {
	for (auto ic = (*it)->begin() ; ic != (*it)->end() ; ++ic)
	  object.push_back(std::make_pair(ic->first->getName(), ic->second));
	if ((*it)->getResult().getItemType() == AItem::STUFF)
	  item = new Stuff(static_cast<Stuff const &>((*it)->getResult()));
	else if ((*it)->getResult().getItemType() == AItem::CONSUMABLE)
	  item = new Consumable(static_cast<Consumable const &>((*it)->getResult()));
	if (item)
	  result.push_back(item);
	exp = this->_currentExp + (*it)->getExp();
	while (this->getExp() < exp)
	  {
	    this->_level->levelUp();
	    exp -= this->getExp();
	  }
	this->_currentExp = exp;
	ret = true;
      }
  return (ret);
}

bool				Job::doGather(std::string const &nameRessource, std::list<AItem *> &result, unsigned int &idRessource)
{
  bool				ret = false;
  unsigned int			exp = 0;

  for (auto it = this->getJobModel().getGathers().begin() ; it != this->getJobModel().getGathers().end() && !ret; ++it)
    if ((*it).getRessource().getName() == nameRessource)
      {
	int			i = rand() % 4 + 1;

	idRessource = (*it).getRessource().getId();
	for (auto nb = 0 ; nb < i ; ++nb)
	  result.push_back(new Ressource((*it).getRessource()));
	exp = this->_currentExp + it->getExp();
	while (this->getExp() < exp)
	  {
	    this->_level->levelUp();
	    exp -= this->getExp();
	  }
	this->_currentExp = exp;
	ret = true;
      }
  return (ret);
}

bool				Job::serialization(Trame &trame) const
{
  bool				ret = true;

  this->_level->serialization(trame);
  this->_jobModel->serialization(trame(trame["MOD"]));
  trame["CEXP"] = this->_currentExp;
  return (ret);
}

Job				*Job::deserialization(Trame const &trame)
{
  Job				*job = new Job;

  job->setLevelObject(*Level::deserialization(trame));
  job->setJobModel(*JobModel::deserialization(trame));
  job->setCurrentExp(trame["CEXP"].asUInt());
  return (job);
}


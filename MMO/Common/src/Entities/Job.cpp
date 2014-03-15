//
// Job.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:04 2014 laurent ansel
// Last update Sat Mar 15 17:46:18 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Job.hh"
#include			"Entities/Stuff.hh"
#include			"Entities/Consumable.hh"
#include			"Loader/LoaderManager.hh"

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

Job::Job(JobModel const &model, Level::type const level) :
  Persistent(), _currentExp(0), _level(new Level(level)), _jobModel(&model)
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

unsigned int			Job::setCurrentExp(unsigned int const currentExp,
						   bool const checkLevelUp)
{
  unsigned int			ret = 0;

  _currentExp = currentExp;
  if (checkLevelUp)
    while (_currentExp < this->getExp()) {
      this->levelUp();
      ret++;
    }
  return (ret);
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

void				Job::resetExp()
{
  this->setExp(this->getExperienceCurve()(this->getLevel()));
  if (this->getCurrentExp() < this->getExperienceCurve()(this->getLevel() - 1) ||
      this->getCurrentExp() >= this->getExperienceCurve()(this->getLevel()))
    this->setCurrentExp(this->getExperienceCurve()(this->getLevel() - 1));
}

ExperienceCurve const		&Job::getExperienceCurve() const
{
  return (this->_jobModel->getExperienceCurve());
}

void				Job::levelUp()
{
  this->setLevel(this->getLevel() + 1);
  this->setExp(this->getExperienceCurve()(this->getLevel()));
}

JobModel const			&Job::getJobModel() const
{
  return (*this->_jobModel);
}

void				Job::setJobModel(JobModel const &jobModel)
{
  this->_jobModel = &jobModel;
}

bool				Job::doCraft(std::string const &nameCraft, Stack<> *&result, std::list<Stack<> *> *&object)
{
  bool				ret = false;
  unsigned int			exp = 0;

  for (auto it = this->getJobModel().getCrafts().begin() ; it != this->getJobModel().getCrafts().end() && !ret; ++it)
    if ((*it)->getName() == nameCraft)
      {
	for (auto ic = (*it)->begin() ; ic != (*it)->end() ; ++ic)
	  object->push_back(*ic);
	result->setItem((*it)->getResult().getItem());
	result->setNb((*it)->getResult().getNb());
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

bool				Job::doGather(std::string const &nameRessource, Stack<AItem> *&result, unsigned int &idRessource)
{
  bool				ret = false;
  unsigned int			exp = 0;
  Ressource			*item;

  for (auto it = this->getJobModel().getGathers().begin() ; it != this->getJobModel().getGathers().end() && !ret; ++it)
    if ((*it).getRessource().getName() == nameRessource)
      {
	int			i = rand() % 4 + 1;

	idRessource = (*it).getRessource().getId();
	// for (auto nb = 0 ; nb < i ; ++nb)
	//   result.push_back(new Ressource((*it).getRessource()));
	item = (**LoaderManager::getInstance()->getRessourceLoader())->getValue((*it).getRessource().getName());
	if (item)
	  {
	    result->setItem(item);
	    result->setNb(i);
	  }
	exp = this->_currentExp + (*it).getExp();
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

bool				Job::doGather(std::string const &nameRessource, Stack<AItem> *&result, unsigned int &idRessource, Carcass *carcass)
{
  bool				ret = false;
  unsigned int			exp = 0;
  Ressource			*item;
  auto				itemCarcass = carcass->begin();

  for (auto it = this->getJobModel().getGathers().begin() ; it != this->getJobModel().getGathers().end() && !ret; ++it)
    if ((*it).getRessource().getName() == nameRessource)
      {
	idRessource = (*it).getRessource().getId();
	item = (**LoaderManager::getInstance()->getRessourceLoader())->getValue((*it).getRessource().getName());
	if (item)
	  {
	    result->setItem(item);
	    for (; itemCarcass != carcass->end() && (*itemCarcass).getItem()->getName() != nameRessource ; ++itemCarcass);
	    if (itemCarcass != carcass->end())
	      result->setNb((*itemCarcass).getNb());
	    else
	      break;
	  }
	exp = this->_currentExp + (*it).getExp();
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
  //  this->_jobModel->serialization(trame(trame["MOD"]));
  trame["MOD"] = this->_jobModel->getName();
  trame["CEXP"] = this->_currentExp;
  return (ret);
}

Job				*Job::deserialization(Trame const &trame)
{
  Job				*job = new Job;

  job->setLevelObject(*Level::deserialization(trame));
  if (trame.isMember("MOD"))
    //    job->setJobModel(*JobModel::deserialization(trame));
    job->setJobModel(*(**LoaderManager::getInstance()->getJobModelLoader())->getValue(trame["MOD"].asString()));
  job->setCurrentExp(trame["CEXP"].asUInt(), false);
  return (job);
}


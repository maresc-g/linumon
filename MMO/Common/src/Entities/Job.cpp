//
// Job.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:04 2014 laurent ansel
// Last update Thu Feb 20 13:26:50 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Job.hh"
#include			"Entities/Stuff.hh"
#include			"Entities/Consumable.hh"

Job::Job():
  Persistent(),
  _currentExp(0),
  _jobModel(NULL)
{
}

Job::~Job()
{
}

Job::Job(Job const &rhs):
  Persistent(rhs)
{
  *this = rhs;
}

Job				&Job::operator=(Job const &rhs)
{
  if (this != &rhs)
    {
      this->setCurrentExp(rhs.getCurrentExp());
      this->setLevel(rhs.getLevel());
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

Level const			&Job::getLevel() const
{
  return (this->_level);
}

void				Job::setLevel(Level const &level)
{
  this->_level = level;
}

JobModel const			&Job::getJobModel() const
{
  return (*this->_jobModel);
}

void				Job::setJobModel(JobModel const &jobModel)
{
  this->_jobModel = &jobModel;
}

bool				Job::doCraft(std::string const &nameCraft, std::list<AItem *> &result, std::list<AItem *> &object)
{
  bool				ret = false;
  unsigned int			exp = 0;
  AItem				*item;

  for (auto it = this->getJobModel().getCrafts().begin() ; it != this->getJobModel().getCrafts().end() && !ret; ++it)
    if ((*it)->getName() == nameCraft)
      {
	for (auto ic = (*it)->getIngredients().begin() ; ic != (*it)->getIngredients().end() ; ++ic)
	  object.push_back(*ic);
	if ((*it)->getResult().getItemType() == AItem::STUFF)
	  item = new Stuff(static_cast<Stuff const &>((*it)->getResult()));
	else if ((*it)->getResult().getItemType() == AItem::CONSUMABLE)
	  item = new Consumable(static_cast<Consumable const &>((*it)->getResult()));
	if (item)
	  result.push_back(item);
	exp = this->_currentExp + (*it)->getLevel().getExp();
	while (this->_level.getExp() < exp)
	  {
	    this->_level.levelUp();
	    exp -= this->_level.getExp();
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

  for (auto it = this->getJobModel().getGather().begin() ; it != this->getJobModel().getGather().end() && !ret; ++it)
    if ((*it)->getName() == nameRessource)
      {
	int			i = rand() % 4 + 1;

	idRessource = (*it)->getId();
	for (auto nb = 0 ; nb < i ; ++nb)
	  result.push_back(new Ressource(**it));
	exp = this->_currentExp + (*it)->getLevel().getExp();
	while (this->_level.getExp() < exp)
	  {
	    this->_level.levelUp();
	    exp -= this->_level.getExp();
	  }
	this->_currentExp = exp;
	ret = true;
      }
  return (ret);
}

bool				Job::serialization(Trame &trame) const
{
  bool				ret = true;

  this->_level.serialization(trame(trame["LEVEL"]));
  this->_jobModel->serialization(trame(trame["JOBMODEL"]));
  trame["EXP"] = this->_currentExp;
  return (ret);
}

Job				*Job::deserialization(Trame const &trame)
{
  Job				*job = new Job;

  job->setLevel(*Level::deserialization(trame));
  job->setJobModel(*JobModel::deserialization(trame));
  job->setCurrentExp(trame["EXP"].asUInt());
  return (job);
}


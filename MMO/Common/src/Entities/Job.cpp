//
// Job.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:04 2014 laurent ansel
// Last update Wed Mar 19 00:03:25 2014 alexis mestag
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
  Levelable(),
  _jobModel(NULL)
{
}

Job::Job(JobModel const &model, Levelable::type const level) :
  Persistent(), Levelable(0, level, 0), _jobModel(&model)
{

}

Job::~Job()
{
#ifndef			CLIENT_COMPILATION
  Repository<Job>	*rj = &Database::getRepository<Job>();
  rj->removeFromCache(*this);
#endif
}

Job::Job(Job const &rhs):
  Persistent(rhs), Levelable(rhs)
{
  *this = rhs;
}

Job				&Job::operator=(Job const &rhs)
{
  if (this != &rhs)
    {
      this->setJobModel(rhs.getJobModel());
    }
  return (*this);
}

#ifndef			CLIENT_COMPILATION
void				Job::resetExp()
{
  this->setExp(this->getExperienceCurve()(this->getLevel() + 1));
  if (this->getCurrentExp() < this->getExperienceCurve()(this->getLevel()) ||
      this->getCurrentExp() >= this->getExperienceCurve()(this->getLevel()))
    this->setCurrentExp(this->getExperienceCurve()(this->getLevel()));
}

ExperienceCurve const		&Job::getExperienceCurve() const
{
  return (this->_jobModel->getExperienceCurve());
}
#endif

void				Job::levelUp()
{
  this->setLevel(this->getLevel() + 1);
#ifndef			CLIENT_COMPILATION
  this->setExp(this->getExperienceCurve()(this->getLevel()));
#endif
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
  // unsigned int			exp = 0;

  for (auto it = this->getJobModel().getCrafts().begin() ; it != this->getJobModel().getCrafts().end() && !ret; ++it)
    if ((*it)->getName() == nameCraft)
      {
	for (auto ic = (*it)->begin() ; ic != (*it)->end() ; ++ic)
	  object->push_back(*ic);
	result->setItem((*it)->getResult().getItem());
	result->setNb((*it)->getResult().getNb());
	// exp = this->_currentExp + (*it)->getExp();
	// while (this->getExp() < exp)
	//   {
	//     this->_level->levelUp();
	//     exp -= this->getExp();
	//   }
	// this->_currentExp = exp;
	this->incCurrentExp((*it)->getExp()); // incCurrentExp() calls levelUp on its own
	ret = true;
      }
  return (ret);
}

bool				Job::doGather(std::string const &nameRessource, Stack<AItem> *&result, unsigned int &idRessource)
{
  bool				ret = false;
  // unsigned int			exp = 0;
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
	// exp = this->_currentExp + (*it).getExp();
	// while (this->getExp() < exp)
	//   {
	//     this->_level->levelUp();
	//     exp -= this->getExp();
	//   }
	// this->_currentExp = exp;
	this->incCurrentExp(it->getExp());
	ret = true;
      }
  return (ret);
}

bool				Job::doGather(std::string const &nameRessource, Stack<AItem> *&result, unsigned int &idRessource, Carcass *carcass)
{
  bool				ret = false;
  // unsigned int			exp = 0;
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
	// exp = this->_currentExp + (*it).getExp();
	// while (this->getExp() < exp)
	//   {
	//     this->_level->levelUp();
	//     exp -= this->getExp();
	//   }
	// this->_currentExp = exp;
	this->incCurrentExp(it->getExp());
	ret = true;
      }
  return (ret);
}

bool				Job::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["EXP"] = this->getExp();
  trame["LVL"] = this->getLevel();
  trame["MOD"] = this->_jobModel->getName();
  trame["CEXP"] = this->getCurrentExp();
  return (ret);
}

Job				*Job::deserialization(Trame const &trame)
{
  Job				*job = new Job;

  if (trame.isMember("MOD"))
    job->setJobModel(*(**LoaderManager::getInstance()->getJobModelLoader())->getValue(trame["MOD"].asString()));
  job->setCurrentExp(trame["CEXP"].asUInt(), false);
  job->setLevel(trame["LVL"].asUInt());
  job->setExp(trame["EXP"].asUInt());
  return (job);
}


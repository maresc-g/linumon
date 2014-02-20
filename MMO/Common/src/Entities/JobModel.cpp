//
// JobModel.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:53:29 2014 laurent ansel
// Last update Thu Feb 20 10:55:30 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/JobModel.hh"

JobModel::JobModel():
  Persistent(),
  Nameable()
{
}

JobModel::~JobModel()
{
}

JobModel::JobModel(JobModel const &rhs):
  Persistent(rhs),
  Nameable(rhs)
{
  *this = rhs;
}

JobModel			&JobModel::operator=(JobModel const &rhs)
{
  if (this != &rhs)
    {
      this->setCrafts(rhs.getCrafts());
      this->setGather(rhs.getGather());
    }
  return (*this);
}

std::list<Craft *> const	&JobModel::getCrafts() const
{
  return (this->_crafts);
}

void				JobModel::setCrafts(std::list<Craft *> const &list)
{
  this->_crafts = list;
}

std::list<Ressource *> const	&JobModel::getGather() const
{
  return (this->_gather);
}

void				JobModel::setGather(std::list<Ressource *> const &list)
{
  this->_gather = list;
}

bool				JobModel::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["JOBMODEL"]["CRAFTS"];
  trame["JOBMODEL"]["GATHER"];
  trame["JOBMODEL"]["NAME"] = this->getName();
  for (auto it = this->_crafts.begin() ; it != this->_crafts.end() && ret; ++it)
    {
      str << "CRAFT" << nb;
      ret = (*it)->serialization(trame(trame["JOBMODEL"]["CRAFTS"][str.str()]));
      str.str("");
      nb++;
    }
  ret = true;
  nb = 0;
  for (auto it = this->_gather.begin() ; it != this->_gather.end() && ret; ++it)
    {
      str << "GATHER" << nb;
      ret = (*it)->serialization(trame(trame["JOBMODEL"]["GATHER"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

JobModel			*JobModel::deserialization(Trame const &trame)
{
  JobModel			*jobModel = NULL;
  std::list<Craft *>		*crafts;
  std::list<Ressource *>	*ressources;
  Craft				*craft;
  Ressource			*ressource;

  if (trame.isMember("JOBMODEL"))
    {
      jobModel = new JobModel;
      jobModel->setName(trame["NAME"].asString());
      crafts = new std::list<Craft *>;
      ressources = new std::list<Ressource *>;

      auto			membersCraft = trame["JOBMODEL"]["CRAFTS"].getMemberNames();
      auto			membersGather = trame["JOBMODEL"]["GATHER"].getMemberNames();

      for (auto it = membersCraft.begin() ; it != membersCraft.end() ; ++it)
	{
	  craft = Craft::deserialization(trame(trame["JOBMODEL"]["CRAFTS"][*it]));
	  if (craft)
	    crafts->push_back(craft);
	}

      for (auto it = membersGather.begin() ; it != membersGather.end() ; ++it)
	{
	  ressource = Ressource::deserialization(trame(trame["JOBMODEL"]["GATHER"][*it]));
	  if (ressource)
	    ressources->push_back(ressource);
	}
      jobModel->setCrafts(*crafts);
      jobModel->setGather(*ressources);
    }
  return (jobModel);
}

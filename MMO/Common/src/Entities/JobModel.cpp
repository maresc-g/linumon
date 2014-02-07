//
// JobModel.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:53:29 2014 laurent ansel
// Last update Fri Feb  7 14:39:42 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/JobModel.hh"

JobModel::JobModel():
  Nameable(""),
  Persistent(),
  _typeJob(eJob::NONE)
{
}

JobModel::~JobModel()
{
}

JobModel::JobModel(JobModel const &rhs):
  Nameable(""),
  Persistent(rhs)
{
  *this = rhs;
}

JobModel			&JobModel::operator=(JobModel const &rhs)
{
  if (this != &rhs)
    {

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

JobModel::eJob			JobModel::getTypeJob() const
{
  return (this->_typeJob);
}

void				JobModel::setTypeJob(JobModel::eJob const typeJob)
{
  this->_typeJob = typeJob;
}

bool				JobModel::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["JOBMODEL"]["CRAFTS"];
  trame["JOBMODEL"]["TYPE"] = this->_typeJob;;
  trame["JOBMODEL"]["NAME"] = this->getName();
  for (auto it = this->_crafts.begin() ; it != this->_crafts.end() && ret; ++it)
    {
      str << "CRAFT" << nb;
      ret = (*it)->serialization(trame(trame["JOBMODEL"]["CRAFTS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

JobModel			*JobModel::deserialization(Trame const &trame)
{
  JobModel			*jobModel = NULL;
  int				nb = 0;
  std::ostringstream		str;
  std::list<Craft *>		*crafts;

  if (trame.isMember("JOBMODEL"))
    {
      jobModel = new JobModel;
      jobModel->setTypeJob(static_cast<JobModel::eJob>(trame["JOBMODEL"]["TYPE"].asUInt()));
      jobModel->setName(trame["NAME"].asString());
      crafts = new std::list<Craft *>;
      str << "CRAFT" << nb;
      for (; !trame["JOBMODEL"]["CRAFTS"].isMember(str.str()) ; ++nb)
	{
	  crafts->push_back(Craft::deserialization(trame(trame["JOBMODEL"]["CRAFTS"][str.str()])));
	  str.str("");
	  str << "CRAFT" << nb + 1;
	}
      jobModel->setCrafts(*crafts);
    }
  return (jobModel);
}


//
// Job.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:04 2014 laurent ansel
// Last update Fri Feb  7 14:45:03 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Job.hh"

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

    }
  return (*this);
}

unsigned int			Job::getCurrentExp() const
{
  return (this->_currentExp);
}

void				Job::setCurrentExp(unsigned int const exp)
{
  this->_currentExp = exp;
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
  *this->_jobModel = jobModel;
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

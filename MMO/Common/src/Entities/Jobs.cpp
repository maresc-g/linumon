//
// Jobs.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 12:53:14 2014 laurent ansel
// Last update Fri Feb  7 14:31:51 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Jobs.hh"

Jobs::Jobs()
{
}

Jobs::Jobs(Jobs const &rhs)
{
  *this = rhs;
}

Jobs::~Jobs()
{

}

Jobs				&Jobs::operator=(Jobs const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

std::list<Job *> const		&Jobs::getJobs() const
{
  return (this->_jobs);
}

void				Jobs::setJobs(std::list<Job *> const &jobs)
{
  this->_jobs = jobs;
}

bool				Jobs::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["JOBS"];
  for (auto it = this->_jobs.begin() ; it!= this->_jobs.end() ; ++it)
    {
      str << "JOB" << nb;
      ret = (*it)->serialization(trame(trame["JOBS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Jobs				*Jobs::deserialization(Trame const &trame)
{
  Jobs				*jobs = NULL;
  std::list<Job *>		*list = NULL;

  if (trame.isMember("JOBS"))
    {
      jobs = new Jobs;
      list = new std::list<Job *>;
      auto			members = trame["JOBS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	list->push_back(Job::deserialization(trame(trame["JOBS"][*it])));
      jobs->setJobs(*list);
    }
  return (jobs);
}
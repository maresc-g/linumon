//
// Jobs.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 12:53:14 2014 laurent ansel
// Last update Mon Mar  3 16:31:27 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Jobs.hh"

Jobs::Jobs() :
  ContainerWrapper<container_type>()
{
}

Jobs::Jobs(Jobs const &rhs) :
  ContainerWrapper<container_type>()
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
      this->setJobs(rhs.getJobs());
    }
  return (*this);
}

Jobs::container_type const	&Jobs::getJobs() const
{
  return (this->getContainer());
}

void				Jobs::setJobs(container_type const &jobs)
{
  this->setContainer(jobs);
}

void				Jobs::setJob(Job *job)
{
  this->getContainer().push_back(job);
}

void				Jobs::setJob(std::string const &name, Job *job)
{
  for (auto it = this->begin() ; it != this->end() ; it++)
    {
      if ((*it)->getJobModel().getName() == name)
	{
	  delete *it;
	  *it = job;
	  break;
	}
    }
}

bool				Jobs::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["JOBS"];
  for (auto it = this->begin() ; it!= this->end() ; ++it)
    {
      str << nb;
      ret = (*it)->serialization(trame(trame["JOBS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Jobs				*Jobs::deserialization(Trame const &trame)
{
  Jobs				*jobs = NULL;
  container_type		*list = NULL;

  if (trame.isMember("JOBS"))
    {
      jobs = new Jobs;
      list = new container_type;
      auto			members = trame["JOBS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	list->push_back(Job::deserialization(trame(trame["JOBS"][*it])));
      jobs->setJobs(*list);
    }
  return (jobs);
}

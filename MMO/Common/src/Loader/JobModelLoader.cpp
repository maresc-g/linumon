//
// JobModelLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 17:33:09 2014 laurent ansel
// Last update Mon Mar 10 19:11:45 2014 alexis mestag
//

#ifndef CLIENT_COMPILATION
# include			"Entities/JobModel-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/JobModelLoader.hh"

/*
**
**	JobModels
**
*/

JobModels::JobModels() :
  _jobModels(new std::list<JobModel *>)
{
#ifndef CLIENT_COMPILATION
  Repository<JobModel>		*mm = &Database::getRepository<JobModel>();

  *_jobModels = mm->getAll();
#endif
}

JobModels::~JobModels()
{
  for (auto it = _jobModels->begin() ; it != _jobModels->end() ; ++it)
    delete *it;
  delete _jobModels;
}

std::list<JobModel *> const	&JobModels::getJobModels() const
{
  return (*this->_jobModels);
}

void				JobModels::addJobModel(JobModel *job)
{
  this->_jobModels->push_back(job);
}

JobModel			*JobModels::getJobModel(std::string const &name) const
{
  for (auto it = _jobModels->begin() ; it != _jobModels->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

/*
**
**	JobModelLoader
**
*/

JobModelLoader::JobModelLoader() :
  _jobModels(new JobModels)
{

}

JobModelLoader::~JobModelLoader()
{
  delete _jobModels;
}

bool				JobModelLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["JOBMODELS"];
  for (auto it = _jobModels->getJobModels().begin() ; it != _jobModels->getJobModels().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["JOBMODELS"][(*it)->getName()]));
  return (ret);
}

bool				JobModelLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  JobModel			*job;

  if (trame[CONTENT].isMember("JOBMODELS"))
    {
      auto			members = trame[CONTENT]["JOBMODELS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  job = JobModel::deserialization(trame(trame[CONTENT]["JOBMODELS"][*it]));
	  if (job)
	    {
	      job->setName(*it);
	      _jobModels->addJobModel(job);
	    }
	}
    }
  return (ret);
}

JobModels const			&JobModelLoader::getLoaderContent() const
{
  return (*_jobModels);
}

JobModels::value		*JobModelLoader::getValue(std::string const &name) const
{
  return (this->_jobModels->getJobModel(name));
}

JobModels::value		*JobModelLoader::getValue(unsigned int const) const
{
  return (NULL);
}

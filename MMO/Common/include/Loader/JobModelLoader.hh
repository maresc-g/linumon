//
// JobModel.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 17:31:12 2014 laurent ansel
// Last update Thu Mar  6 11:09:34 2014 laurent ansel
//

#ifndef 			__JOBMODELLOADER_HH__
# define 			__JOBMODELLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/JobModel.hh"

class				JobModels
{
public:
  typedef JobModel		value;

private:
  void				setJobModels(std::list<JobModel *> const &jobModels);

private:
  std::list<JobModel *>		*_jobModels;

public:
  JobModels();
  virtual ~JobModels();

  std::list<JobModel *> const	&getJobModels() const;

  void				addJobModel(JobModel *job);

  JobModel			*getJobModel(std::string const &name) const;
};

class				JobModelLoader : public ILoader<JobModels>
{
private:
  JobModels			*_jobModels;
public:
  JobModelLoader();
  virtual ~JobModelLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual JobModels const	&getLoaderContent() const;
  virtual JobModels::value	*getValue(std::string const &name) const;
  virtual JobModels::value	*getValue(unsigned int const id) const;
};

#endif

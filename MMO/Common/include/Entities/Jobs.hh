//
// Jobs.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 12:52:53 2014 laurent ansel
// Last update Sun Mar 23 19:50:06 2014 laurent ansel
//

#ifndef 			__JOBS_HH__
# define 			__JOBS_HH__

# include			"Entities/Job.hh"
# include			"Utility/ISerialization.hh"
# include			"Utility/Wrapper.hpp"

class				Jobs : public ISerialization, public ContainerWrapper<std::list<Job *> >
{
private:
  void				deleteJobs();

public:
  Jobs();
  Jobs(Jobs const &rhs);
  virtual ~Jobs();

  Jobs				&operator=(Jobs const &rhs);

  container_type const		&getJobs() const;
  void				setJobs(container_type const &jobs);
  void				setJob(Job *job);
  void				setJob(std::string const &name, Job *job);

  Job				*getJobWithRessource(std::string const &gather) const;

  virtual bool			serialization(Trame &trame) const;
  static Jobs			*deserialization(Trame const &trame);
};

#endif

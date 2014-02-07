//
// Jobs.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 12:52:53 2014 laurent ansel
// Last update Fri Feb  7 14:23:24 2014 laurent ansel
//

#ifndef 			__JOBS_HH__
# define 			__JOBS_HH__

#include			"Entities/Job.hh"
#include			"Utility/ISerialization.hh"

class				Jobs : public ISerialization
{
  friend class			odb::access;

private:
  std::list<Job *>		_jobs;

  Jobs();

public:

  Jobs(Jobs const &rhs);

  Jobs				&operator=(Jobs const &rhs);

  virtual ~Jobs();

  std::list<Job *> const	&getJobs() const;
  void				setJobs(std::list<Job *> const &jobs);

  virtual bool			serialization(Trame &trame) const;
  static Jobs			*deserialization(Trame const &trame);
};

#endif

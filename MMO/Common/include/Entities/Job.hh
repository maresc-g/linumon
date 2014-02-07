//
// Job.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:19 2014 laurent ansel
// Last update Fri Feb  7 14:01:34 2014 laurent ansel
//

#ifndef 		__JOB_HH__
# define 		__JOB_HH__

#include		"Entities/Level.hh"
#include		"Entities/JobModel.hh"

class			Job : public ISerialization, public Persistent
{
  friend class		odb::access;

private:
  unsigned int		_currentExp;
  Level			_level;
  JobModel		*_jobModel;

  Job();

  void			setCurrentExp(unsigned int const exp);
  void			setLevel(Level const &level);
  void			setJobModel(JobModel const &model);

public:
  Job(Job const &rhs);
  Job			&operator=(Job const &rhs);

  virtual ~Job();

  unsigned int		getCurrentExp() const;
  Level const		&getLevel() const;
  JobModel const	&getJobModel() const;

  virtual bool		serialization(Trame &trame) const;
  static Job		*deserialization(Trame const &trame);
};

#endif

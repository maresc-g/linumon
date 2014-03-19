//
// Job.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:19 2014 laurent ansel
// Last update Wed Mar 19 00:22:14 2014 alexis mestag
//

#ifndef 		__JOB_HH__
# define 		__JOB_HH__

#include		"Entities/Levelable.hh"
#include		"Entities/JobModel.hh"
#include		"Entities/Carcass.hh"

class			Job : public Persistent, public Levelable, public ISerialization
{
  friend class		odb::access;

private:
  JobModel const	*_jobModel;

  Job();

public:
  Job(JobModel const &model, Levelable::type const level = 0);
  Job(Job const &rhs);
  virtual ~Job();

  Job			&operator=(Job const &rhs);

# ifndef	CLIENT_COMPILATION
  void			resetExp();
  ExperienceCurve const	&getExperienceCurve() const;
# endif
  virtual void		levelUp();

  JobModel const	&getJobModel() const;
  void			setJobModel(JobModel const &jobModel);

  bool			doCraft(std::string const &nameCraft, Stack<> *&result, std::list<Stack<> *> *&object);
  bool			doGather(std::string const &nameRessource, Stack<> *&result, unsigned int &idRessource);
  bool			doGather(std::string const &nameRessource, Stack<> *&result, unsigned int &idRessource, Carcass *carcass);

  virtual bool		serialization(Trame &trame) const;
  static Job		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Job)
#  pragma db member(Job::currentExp) virtual(Levelable::type) get(getCurrentExp()) set(setCurrentExp((?), false))
#  pragma db member(Job::level) virtual(Levelable::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Job::exp) virtual(Levelable::type) get(getExp()) set(setExp(?))
#  pragma db member(Job::_jobModel) not_null
# endif

#endif

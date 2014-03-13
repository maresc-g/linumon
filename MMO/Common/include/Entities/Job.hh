//
// Job.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:19 2014 laurent ansel
// Last update Thu Mar 13 12:38:35 2014 alexis mestag
//

#ifndef 		__JOB_HH__
# define 		__JOB_HH__

#include		"Entities/Level.hh"
#include		"Entities/JobModel.hh"

class			Job : public Persistent, public ISerialization
{
  friend class		odb::access;

private:
  unsigned int		_currentExp;
  Level			*_level;
  JobModel const	*_jobModel;

  Job();

public:
  Job(JobModel const &model, Level::type const level = 0);
  Job(Job const &rhs);
  virtual ~Job();

  Job			&operator=(Job const &rhs);

  unsigned int		getCurrentExp() const;
  unsigned int		setCurrentExp(unsigned int const currentExp, bool const checkLevelUp = true);

  Level const		&getLevelObject() const;
  void			setLevelObject(Level const &level);

  Level::type		getLevel() const;
  void			setLevel(Level::type const level);

  Level::type		getExp() const;
  void			setExp(Level::type const exp);
  void			resetExp();

  ExperienceCurve const	&getExperienceCurve() const;
  void			levelUp();

  JobModel const	&getJobModel() const;
  void			setJobModel(JobModel const &jobModel);

  bool			doCraft(std::string const &nameCraft, std::list<AItem *> &result, std::list<std::pair<std::string, unsigned int> > &object);
  bool			doGather(std::string const &nameRessource, std::list<AItem *> &result, unsigned int &idRessource);

  virtual bool		serialization(Trame &trame) const;
  static Job		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Job)
#  pragma db member(Job::_level) transient
#  pragma db member(Job::_currentExp) get(getCurrentExp()) set(setCurrentExp((?), false))
#  pragma db member(Job::level) virtual(Level::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Job::exp) virtual(Level::type) get(getExp()) set(setExp(?))
#  pragma db member(Job::_jobModel) not_null
# endif

#endif

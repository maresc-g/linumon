//
// Job.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:11:19 2014 laurent ansel
// Last update Thu Feb 27 14:00:07 2014 laurent ansel
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
  Level			_level;
  JobModel const	*_jobModel;

  Job();

public:
  Job(Job const &rhs);
  virtual ~Job();

  Job			&operator=(Job const &rhs);

  unsigned int		getCurrentExp() const;
  void			setCurrentExp(unsigned int const currentExp);

  Level const		&getLevel() const;
  void			setLevel(Level const &level);

  JobModel const	&getJobModel() const;
  void			setJobModel(JobModel const &jobModel);

  bool			doCraft(std::string const &nameCraft, std::list<AItem *> &result, std::list<std::pair<std::string, unsigned int> > &object);
  bool			doGather(std::string const &nameRessource, std::list<AItem *> &result, unsigned int &idRessource);

  virtual bool		serialization(Trame &trame) const;
  static Job		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Job)
# endif

#endif

//
// JobModel.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:21:21 2014 laurent ansel
// Last update Mon Feb 10 10:52:36 2014 alexis mestag
//

#ifndef 		__JOBMODEL_HH__
# define 		__JOBMODEL_HH__

#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Craft.hh"

class			JobModel : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  std::list<Craft *>	_crafts;

  JobModel();

  void			setCrafts(std::list<Craft *> const &crafts);

public:
  JobModel(JobModel const &rhs);
  virtual ~JobModel();

  JobModel			&operator=(JobModel const &rhs);

  std::list<Craft *> const	&getCrafts() const;

  virtual bool		serialization(Trame &trame) const;
  static JobModel	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(JobModel)
# endif

#endif

//
// JobModel.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:21:21 2014 laurent ansel
// Last update Fri Feb  7 14:24:11 2014 laurent ansel
//

#ifndef 		__JOBMODEL_HH__
# define 		__JOBMODEL_HH__

#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Craft.hh"

class			JobModel : public ISerialization, public Nameable, public Persistent
{
  friend class		odb::access;

public:
  typedef enum		eJob
    {
      NONE,
      DIGITALISER,
      CARTOUCHE,
      OBJECT1,
      OBJECT2,
      POTION,
      HERBO,
      MINOR
    }			eJob;

private:
  eJob			_typeJob;
  std::list<Craft *>	_crafts;

  JobModel();

  void			setCrafts(std::list<Craft *> const &crafts);
  void			setTypeJob(JobModel::eJob const type);

public:
  JobModel(JobModel const &rhs);
  JobModel		&operator=(JobModel const &rhs);

  virtual ~JobModel();

  JobModel::eJob	getTypeJob() const;
  std::list<Craft *> const	&getCrafts() const;

  virtual bool		serialization(Trame &trame) const;
  static JobModel	*deserialization(Trame const &trame);
};

#endif

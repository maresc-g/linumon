//
// JobModel.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:21:21 2014 laurent ansel
// Last update Fri Feb 28 15:09:32 2014 laurent ansel
//

#ifndef 		__JOBMODEL_HH__
# define 		__JOBMODEL_HH__

#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Craft.hh"
#include		"Entities/Gather.hh"
#include		"Entities/Ressource.hh"

class			JobModel : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  std::string		_path;
  std::list<Craft *>	*_crafts;
  std::list<Gather>	_gather;

  JobModel();

  void			setCrafts(std::list<Craft *> const &crafts);
  void			setGather(std::list<Gather> const &gather);

public:
  JobModel(JobModel const &rhs);
  virtual ~JobModel();

  JobModel			&operator=(JobModel const &rhs);

  void				loadCrafts();
  void				serializationCrafts();

  std::list<Craft *> const	&getCrafts() const;
  Craft const			*getCraft(std::string const &name) const;
  std::list<Gather> const	&getGather() const;

  std::string const	&getPath() const;
  void			setPath(std::string const &path);

  virtual bool		serialization(Trame &trame) const;
  static JobModel	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(JobModel)
#  pragma db member(JobModel::_crafts) transient
#  pragma db member(JobModel::_path) get(getPath()) set(setPath(?))
# endif

#endif

//
// JobModel.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:21:21 2014 laurent ansel
// Last update Tue Mar 18 11:24:06 2014 alexis mestag
//

#ifndef 		__JOBMODEL_HH__
# define 		__JOBMODEL_HH__

#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Craft.hh"
#include		"Entities/Gather.hh"
#include		"Entities/Ressource.hh"
#include		"Stats/ExperienceCurve.hh"

class				JobModel : public Persistent, public Nameable, public ISerialization
{
  friend class			odb::access;

public:
  typedef std::list<Gather>	gathers_container_type;

private:
  std::string			_path;
  std::list<Craft *>		*_crafts;
  std::list<Gather>		*_gathers;
# ifndef	CLIENT_COMPILATION
  ExperienceCurve const		*_expCurve;
# endif

  JobModel();

  void				setCrafts(std::list<Craft *> const &crafts);
  void				setGathers(std::list<Gather> const &gathers);

# ifndef	CLIENT_COMPILATION
  void				setExperienceCurve(ExperienceCurve const &expCurve);
# endif
public:
  JobModel(JobModel const &rhs);
  virtual ~JobModel();

  JobModel			&operator=(JobModel const &rhs);

  void				loadCrafts();
  void				serializationCrafts();

  std::list<Craft *> const	&getCrafts() const;
  Craft const			*getCraft(std::string const &name) const;
  std::list<Gather> const	&getGathers() const;

  std::string const		&getPath() const;
  void				setPath(std::string const &path);

# ifndef	CLIENT_COMPILATION
  ExperienceCurve const		&getExperienceCurve() const;
# endif

  virtual bool			serialization(Trame &trame) const;
  static JobModel		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(JobModel)
#  pragma db member(JobModel::_crafts) transient
#  pragma db member(JobModel::_gathers) transient
#  pragma db member(JobModel::_path) get(getPath()) set(setPath(?))
#  pragma db member(JobModel::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(JobModel::gathers) virtual(JobModel::gathers_container_type) get(getGathers()) set(setGathers(?)) value_not_null
#  pragma db member(JobModel::_expCurve) not_null
# endif

#endif

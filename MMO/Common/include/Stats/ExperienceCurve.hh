//
// ExperienceCurve.hh for ExperienceCurve in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 14:06:26 2014 alexis mestag
// Last update Fri Mar 14 15:26:01 2014 laurent ansel
//

#ifndef				__EXPERIENCECURVE_HH__
# define			__EXPERIENCECURVE_HH__

# include			"Database/Persistent.hh"
# include			"DynamicLibrary/IDynamicLibrary.hh"
# include			"Mutex/IMutex.hh"
# include			"Stats/IExperienceFunction.hpp"
# include			"Utility/Nameable.hh"

class				ExperienceCurve : public Persistent, public Nameable
{
  friend class			odb::access;

private:
  IDynamicLibrary		*_dl;
  IExperienceFunction		*_f;
  IMutex			*_mtx;

private:
  ExperienceCurve();
  ExperienceCurve(ExperienceCurve const &rhs);

  ExperienceCurve		&operator=(ExperienceCurve const &rhs);

  IExperienceFunction const	&getExperienceFunction() const;

public:
  ExperienceCurve(std::string const &name, std::string const &path);
  virtual ~ExperienceCurve();

  Level::type			operator()(Level::type const level) const;

  std::string const		&getPath() const;
  void				setPath(std::string const &path);
};

# ifdef	ODB_COMPILER
#  pragma db object(ExperienceCurve)
#  pragma db member(ExperienceCurve::_dl) transient
#  pragma db member(ExperienceCurve::_f) transient
#  pragma db member(ExperienceCurve::_mtx) transient
#  pragma db member(ExperienceCurve::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(ExperienceCurve::path) virtual(std::string) get(getPath()) set(setPath(?))
# endif

#endif

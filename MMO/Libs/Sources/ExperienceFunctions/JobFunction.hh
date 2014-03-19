//
// JobFunction.hh for JobFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 19:19:28 2014 alexis mestag
// Last update Tue Mar 18 23:01:15 2014 alexis mestag
//

#ifndef				__JOBFUNCTION_HH__
# define			__JOBFUNCTION_HH__

# include			"Stats/IExperienceFunction.hpp"

class				JobFunction : public IExperienceFunction
{
public:
  JobFunction();
  virtual ~JobFunction();

public:
  virtual Levelable::type	operator()(Levelable::type const level) const;
};

extern				"C"
{
  JobFunction			*getInstance() {
    return (new JobFunction());
  }
}

#endif

//
// JobFunction.hh for JobFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 19:19:28 2014 alexis mestag
// Last update Wed Mar 12 19:23:47 2014 alexis mestag
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
  virtual Level::type		operator()(Level::type const level) const;
};

extern				"C"
{
  JobFunction			*getInstance() {
    return (new JobFunction());
  }
}

#endif

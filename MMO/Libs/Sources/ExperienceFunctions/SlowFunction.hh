//
// SlowFunction.hh for SlowFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:42:37 2014 alexis mestag
// Last update Tue Mar 18 23:00:37 2014 alexis mestag
//

#ifndef				__SLOWFUNCTION_HH__
# define			__SLOWFUNCTION_HH__

# include			"Stats/IExperienceFunction.hpp"

class				SlowFunction : public IExperienceFunction
{
public:
  SlowFunction();
  virtual ~SlowFunction();

public:
  virtual Levelable::type	operator()(Levelable::type const level) const;
};

extern				"C"
{
  SlowFunction			*getInstance() {
    return (new SlowFunction());
  }
}

#endif

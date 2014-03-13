//
// SlowFunction.hh for SlowFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:42:37 2014 alexis mestag
// Last update Wed Mar 12 16:44:33 2014 alexis mestag
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
  virtual Level::type		operator()(Level::type const level) const;
};

extern				"C"
{
  SlowFunction			*getInstance() {
    return (new SlowFunction());
  }
}

#endif

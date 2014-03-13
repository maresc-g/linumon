//
// ParabolicFunction.hh for ParabolicFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:15:23 2014 alexis mestag
// Last update Wed Mar 12 16:18:34 2014 alexis mestag
//

#ifndef				__PARABOLICFUNCTION_HH__
# define			__PARABOLICFUNCTION_HH__

# include			"Stats/IExperienceFunction.hpp"

class				ParabolicFunction : public IExperienceFunction
{
public:
  ParabolicFunction();
  virtual ~ParabolicFunction();

public:
  virtual Level::type		operator()(Level::type const level) const;
};

extern				"C"
{
  ParabolicFunction		*getInstance() {
    return (new ParabolicFunction());
  };
}

#endif

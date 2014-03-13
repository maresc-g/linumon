//
// FastFunction.hh for FastFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:35:16 2014 alexis mestag
// Last update Wed Mar 12 19:33:14 2014 alexis mestag
//

#ifndef				__FASTFUNCTION_HH__
# define			__FASTFUNCTION_HH__

# include			"Stats/IExperienceFunction.hpp"

class				FastFunction : public IExperienceFunction
{
public:
  FastFunction();
  virtual ~FastFunction();

public:
  virtual Level::type		operator()(Level::type const level) const;
};

extern				"C"
{
  FastFunction			*getInstance() {
    return (new FastFunction());
  }
}

#endif

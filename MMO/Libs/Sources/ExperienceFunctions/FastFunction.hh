//
// FastFunction.hh for FastFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:35:16 2014 alexis mestag
// Last update Tue Mar 18 23:01:27 2014 alexis mestag
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
  virtual Levelable::type	operator()(Levelable::type const level) const;
};

extern				"C"
{
  FastFunction			*getInstance() {
    return (new FastFunction());
  }
}

#endif

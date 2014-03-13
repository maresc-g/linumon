//
// MediumFunction.hh for MediumFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:28:30 2014 alexis mestag
// Last update Wed Mar 12 16:30:25 2014 alexis mestag
//

#ifndef				__MEDIUMFUNCTION_HH__
# define			__MEDIUMFUNCTION_HH__

# include			"Stats/IExperienceFunction.hpp"

class				MediumFunction : public IExperienceFunction
{
public:
  MediumFunction();
  virtual ~MediumFunction();

public:
  virtual Level::type		operator()(Level::type const level) const;
};

extern				"C"
{
  MediumFunction		*getInstance() {
    return (new MediumFunction());
  }
}

#endif

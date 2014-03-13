//
// IExperienceFunction.hh for IExperienceFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 14:45:46 2014 alexis mestag
// Last update Wed Mar 12 14:50:37 2014 alexis mestag
//

#ifndef				__IEXPERIENCEFUNCTION_HPP__
# define			__IEXPERIENCEFUNCTION_HPP__

# include			"Entities/Level.hh"

class				IExperienceFunction
{
public:
  virtual ~IExperienceFunction() {}

  virtual Level::type		operator()(Level::type const level) const = 0;
};

#endif

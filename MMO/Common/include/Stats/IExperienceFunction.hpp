//
// IExperienceFunction.hh for IExperienceFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 14:45:46 2014 alexis mestag
// Last update Tue Mar 18 23:54:18 2014 alexis mestag
//

#ifndef				__IEXPERIENCEFUNCTION_HPP__
# define			__IEXPERIENCEFUNCTION_HPP__

# include			"Entities/Levelable.hh"

class				IExperienceFunction
{
public:
  virtual ~IExperienceFunction() {}

  virtual Levelable::type	operator()(Levelable::type const level) const = 0;
};

#endif

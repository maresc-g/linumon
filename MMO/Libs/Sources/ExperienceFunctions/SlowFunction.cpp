//
// SlowFunction.cpp for SlowFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:40:48 2014 alexis mestag
// Last update Tue Mar 18 23:00:47 2014 alexis mestag
//

#include				<cmath>
#include				"SlowFunction.hh"

SlowFunction::SlowFunction()
{

}

SlowFunction::~SlowFunction()
{

}

Levelable::type				SlowFunction::operator()(Levelable::type const level) const
{
  return (1.25 * std::pow(level, 3));
}

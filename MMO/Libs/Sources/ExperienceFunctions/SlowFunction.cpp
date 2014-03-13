//
// SlowFunction.cpp for SlowFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:40:48 2014 alexis mestag
// Last update Wed Mar 12 23:09:58 2014 alexis mestag
//

#include				<cmath>
#include				"SlowFunction.hh"

SlowFunction::SlowFunction()
{

}

SlowFunction::~SlowFunction()
{

}

Level::type				SlowFunction::operator()(Level::type const level) const
{
  return (1.25 * std::pow(level + 1, 3));
}

//
// FastFunction.cpp for FastFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:32:58 2014 alexis mestag
// Last update Tue Mar 18 23:01:31 2014 alexis mestag
//

#include				<cmath>
#include				"FastFunction.hh"

FastFunction::FastFunction()
{

}

FastFunction::~FastFunction()
{

}

Levelable::type				FastFunction::operator()(Levelable::type const level) const
{
  return (0.8 * std::pow(level, 3));
}

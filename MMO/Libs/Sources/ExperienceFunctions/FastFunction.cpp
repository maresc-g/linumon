//
// FastFunction.cpp for FastFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:32:58 2014 alexis mestag
// Last update Wed Mar 12 23:09:34 2014 alexis mestag
//

#include				<cmath>
#include				"FastFunction.hh"

FastFunction::FastFunction()
{

}

FastFunction::~FastFunction()
{

}

Level::type				FastFunction::operator()(Level::type const level) const
{
  return (0.8 * std::pow(level + 1, 3));
}

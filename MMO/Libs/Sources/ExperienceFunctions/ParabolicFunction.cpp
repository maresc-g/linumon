//
// ParabolicFunction.cpp for ParabolicFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:18:55 2014 alexis mestag
// Last update Tue Mar 18 23:00:57 2014 alexis mestag
//

#include				<cmath>
#include				"ParabolicFunction.hh"

ParabolicFunction::ParabolicFunction()
{

}

ParabolicFunction::~ParabolicFunction()
{

}

Levelable::type				ParabolicFunction::operator()(Levelable::type const level) const
{
  return (1.2 * std::pow(level, 3) - 15 * std::pow(level, 2) + 100 * level - 140);
}

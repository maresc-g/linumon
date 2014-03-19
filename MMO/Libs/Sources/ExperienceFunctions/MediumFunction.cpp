//
// MediumFunction.cpp for MediumFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:28:34 2014 alexis mestag
// Last update Tue Mar 18 23:01:10 2014 alexis mestag
//

#include				<cmath>
#include				"MediumFunction.hh"

MediumFunction::MediumFunction()
{

}

MediumFunction::~MediumFunction()
{

}

Levelable::type				MediumFunction::operator()(Levelable::type const level) const
{
  return (std::pow(level, 3));
}

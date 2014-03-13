//
// MediumFunction.cpp for MediumFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/ExperienceCurves
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 16:28:34 2014 alexis mestag
// Last update Wed Mar 12 23:09:47 2014 alexis mestag
//

#include				<cmath>
#include				"MediumFunction.hh"

MediumFunction::MediumFunction()
{

}

MediumFunction::~MediumFunction()
{

}

Level::type				MediumFunction::operator()(Level::type const level) const
{
  return (std::pow(level + 1, 3));
}

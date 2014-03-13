//
// JobFunction.cpp for JobFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 19:20:48 2014 alexis mestag
// Last update Wed Mar 12 23:09:41 2014 alexis mestag
//

#include				<cmath>
#include				"JobFunction.hh"

JobFunction::JobFunction()
{

}

JobFunction::~JobFunction()
{

}

Level::type				JobFunction::operator()(Level::type const level) const
{
  return (std::pow(level + 1, 2) * 100);
}

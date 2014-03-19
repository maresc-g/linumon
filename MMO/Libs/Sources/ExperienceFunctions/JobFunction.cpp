//
// JobFunction.cpp for JobFunction in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 19:20:48 2014 alexis mestag
// Last update Tue Mar 18 23:01:22 2014 alexis mestag
//

#include				<cmath>
#include				"JobFunction.hh"

JobFunction::JobFunction()
{

}

JobFunction::~JobFunction()
{

}

Levelable::type				JobFunction::operator()(Levelable::type const level) const
{
  return (std::pow(level, 2) * 100);
}

//
// AMutex.cpp for AMutex in /home/mestag_a/Documents/Projets/Tek3/Babel/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov 25 21:12:25 2013 alexis mestag
// Last update Mon Nov 25 22:47:08 2013 alexis mestag
//

#include			"Mutex/AMutex.hh"

AMutex::AMutex() :
  _isInit(false)
{

}

AMutex::~AMutex()
{

}

void				AMutex::setIsInit(bool const init)
{
  _isInit = init;
}

bool				AMutex::isInit() const
{
  return (_isInit);
}

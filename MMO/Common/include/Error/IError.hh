//
// IError.hh for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Oct 30 15:37:31 2013 laurent ansel
// Last update Wed Oct 30 15:50:34 2013 laurent ansel
//

#ifndef				__IERROR_HPP__
#define				__IERROR_HPP__

#include			<string>
#include			<iostream>
#include			<sstream>
#include			<exception>

class				IError : public std::exception
{
public:
  virtual ~IError() throw(){}
  virtual char const		*what() const throw() = 0;
};

#endif

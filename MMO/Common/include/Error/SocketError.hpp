//
// AError.hpp for  in /home/ansel_l/Documents/Rtype/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Oct 30 15:37:54 2013 laurent ansel
// Last update Tue Nov 12 13:01:34 2013 guillaume marescaux
//

#ifndef			__SOCKETERROR_HPP__
# define		__SOCKETERROR_HPP__

#include		"Error/IError.hh"

class			SocketError : public IError
{
private:
  std::string		_msg;

public:
  SocketError(std::string const &msg):
    _msg("")
  {
    _msg = "Error Socket : " + msg;
  }
  virtual ~SocketError() throw(){}
  virtual char const	*what() const throw()
  {
    return (_msg.c_str());
  }
};

#endif

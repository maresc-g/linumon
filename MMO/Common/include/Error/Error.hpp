//
// Error.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Jan 25 14:45:20 2014 laurent ansel
// Last update Mon Jan 27 13:16:36 2014 laurent ansel
//

#ifndef			__ERROR_HPP__
# define		__ERROR_HPP__

#include		"Error/IError.hh"
#include		"Utility/ISerialization.hh"

class			Error : public IError, public ISerialization
{
public:
  enum			eError
    {
      USER,
      NOTHING
    };

private:
  std::string		_msg;
  enum eError		_type;
public:
  Error(enum eError const type = NOTHING):
    _msg(""),
    _type(type)
  {
    if (type != NOTHING)
      buildError();
  }
  virtual ~Error() throw(){}
  virtual char const	*what() const throw()
  {
    return (_msg.c_str());
  }
  virtual bool			serialization(Trame &trame) const
  {
    trame[CONTENT]["ERROR"] = this->_type;
    return (true);
  }

  virtual bool			deserialization(Trame const &trame)
  {
    if (trame[CONTENT].isMember("ERROR"))
      {
	this->_type = static_cast<enum eError>(trame[CONTENT]["ERROR"].asInt());
	buildError();
	return (true);
      }
    return (false);
  }

  void				setType(enum eError const type)
  {
    this->_type = type;
  }
private:
  void				buildError()
  {
    static std::map<enum eError, std::string> map =
      {
	{USER, "bad username or pass"}
      };
    _msg = "Error  : " + map[_type];
  }
};


#endif

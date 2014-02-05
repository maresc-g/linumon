//
// Error.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Jan 25 14:45:20 2014 laurent ansel
// Last update Tue Feb  4 15:04:46 2014 laurent ansel
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
      USERCONNECTED,
      CREATEPLAYER,
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

  static Error			*deserialization(Trame const &trame)
  {
    Error			*error = NULL;

    if (trame[CONTENT].isMember("ERROR"))
      {
	error = new Error(static_cast<enum eError>(trame[CONTENT]["ERROR"].asInt()));
	error->buildError();
      }
    return (error);
  }

  void				setType(enum eError const type)
  {
    this->_type = type;
  }

  eError			getType(void) const
  {
    return (_type);
  }

  void				buildError()
  {
    static std::map<enum eError, std::string> map =
      {
	{USER,		"bad username or pass"},
	{USERCONNECTED,	"user already connected"},
	{CREATEPLAYER,	"name already exist"}
      };
    _msg = "Error  : " + map[_type];
  }
};


#endif

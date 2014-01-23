//
// Trame.hh for  in /home/ansel_l/Documents/Pfa/work/Common/include/Trame
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:57:30 2013 laurent ansel
// Last update Thu Dec  5 13:30:00 2013 laurent ansel
//

#ifndef 			__TRAME_HH__
# define 			__TRAME_HH__

#include			<jsoncpp/json/json.h>
#include			"Utility/CommonDefine.hh"

#define	TRAMEEND		"<TRAMEEND>"

class				Trame : public Json::Value
{
private:
  bool				_end;
  size_t			_size;
public:
  Trame(bool const end = false);
  Trame(std::string const &str, bool const end = false);
  virtual ~Trame();
  bool				toString(std::string &content) const;
  bool				writeInFile(std::string const &filename) const;
  bool				getEnd() const;
  void				setEnd(bool const end);
  void				setSize(size_t const size);
  static void			removeTrameEnd(std::string &content);
  static bool			isEnd(std::string const &content);
  static bool			readFile(Trame &trame, std::string const &filename);
  static bool			toTrame(Trame &trame, std::string const &content);
};

#endif
//
// Trame.hh for  in /home/ansel_l/Documents/Pfa/work/Common/include/Trame
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:57:30 2013 laurent ansel
// Last update Thu Jan 30 12:34:36 2014 laurent ansel
//

#ifndef 			__TRAME_HH__
# define 			__TRAME_HH__

#include			"JsonFile/JsonFile.hh"
#include			"Utility/CommonDefine.hh"

#define	TRAMEEND		"<TRAMEEND>"

class				Trame : public JsonFile
{
private:
  bool				_end;
  size_t			_size;
public:
  Trame(bool const end = false);
  Trame(std::string const &str, bool const end = false);
  virtual ~Trame();
  // Trame				&operator[](std::string const &key) const;
  void				setSize(size_t const size);
  virtual bool			toString(std::string &content) const;
  std::string			toString() const;
  bool				getEnd() const;
  void				setEnd(bool const end);
  static void			removeTrameEnd(std::string &content);
  static bool			isEnd(std::string const &content);

  /*
  ** renvoie -1 error
  ** renvoie 1 s'il y a encore du json à parser
  ** renvoie 0 si tout est bon x)
  */
  static int			toTrame(Trame &trame, std::string const &content);
};

#endif

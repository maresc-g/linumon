//
// Json.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Jan 30 11:16:58 2014 laurent ansel
// Last update Thu Jan 30 12:34:24 2014 laurent ansel
//

#ifndef 			__JSONFILE_HH__
# define 			__JSONFILE_HH__

#include			<jsoncpp/json/json.h>
#include			"Utility/CommonDefine.hh"

class				JsonFile : public Json::Value
{
public:
  JsonFile();
  virtual ~JsonFile();
  virtual bool			toString(std::string &content) const;
  bool				writeInFile(std::string const &filename) const;
  static bool			readFile(JsonFile &trame, std::string const &filename);
};

#endif

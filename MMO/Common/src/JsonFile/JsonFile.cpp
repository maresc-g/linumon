//
// Json.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Jan 30 11:18:31 2014 laurent ansel
// Last update Mon Feb 24 13:18:56 2014 laurent ansel
//

#include		<sstream>
#include		<fstream>
#include		"JsonFile/JsonFile.hh"

JsonFile::JsonFile():
  JsonFile::Value()
{

}

JsonFile::~JsonFile()
{
}

bool			JsonFile::toString(std::string &content) const
{
  Json::FastWriter	*writer = new Json::FastWriter;
  std::string		str(CONTENT + std::string(" : "));

  content = writer->write(*this);
  delete writer;
  return (true);
}

bool			JsonFile::writeInFile(std::string const &filename) const
{
  std::ofstream		file(filename);
  std::string		str;

  if (this->toString(str))
    {
      file.write(str.c_str(), str.size());
      file.close();
    }
  return (false);
}

bool			JsonFile::readFile(JsonFile &json, std::string const &filename)
{
  bool			ret;
  std::ifstream		str(filename, std::ifstream::binary);
  Json::Reader	*reader = new Json::Reader;

  ret = reader->parse(str, json);
  delete reader;
  str.close();
  return (ret);
}

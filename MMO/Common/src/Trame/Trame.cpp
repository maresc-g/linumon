//
// Trame.cpp for  in /home/ansel_l/Documents/Pfa/work/Common/src/Trame
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:55:14 2013 laurent ansel
// Last update Fri Nov 29 15:42:16 2013 laurent ansel
//

#include		<sstream>
#include		<fstream>
#include		"Trame/Trame.hh"

Trame::Trame(bool const end):
  Json::Value(),
  _end(end)
{

}

Trame::Trame(std::string const &str, bool const end):
  Json::Value(),
  _end(end)
{
  Trame::toTrame(*this, str);
}

Trame::~Trame()
{

}

bool			Trame::toString(std::string &content) const
{
  Json::StyledWriter	*writer = new Json::StyledWriter;

  content = writer->write(*this);
  delete writer;
  if (this->_end)
    content.append(TRAMEEND);
  return (true);
}

bool			Trame::writeInFile(std::string const &filename) const
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

void			Trame::setEnd(bool const end)
{
  this->_end = end;
}

bool			Trame::getEnd() const
{
  return (this->_end);
}

void			Trame::removeTrameEnd(std::string &content)
{
  size_t		pos;

  if (!content.empty() && (pos = content.find(TRAMEEND)) != std::string::npos)
    content = content.substr(0, pos);
}

bool			Trame::isEnd(std::string const &content)
{
  if (!content.empty() && (content.find(TRAMEEND) != std::string::npos))
    return (true);
  return (false);
}

bool			Trame::readFile(Trame &trame, std::string const &filename)
{
  bool			ret;
  std::ifstream		str(filename, std::ifstream::binary);
  Json::Reader		*reader = new Json::Reader;

  ret = reader->parse(str, trame);
  delete reader;
  str.close();
  return (ret);
}

bool			Trame::toTrame(Trame &trame, std::string const &str)
{
  std::string		tmp = str;
  bool			ret;
  Json::Reader		*reader = new Json::Reader;

  trame.setEnd(Trame::isEnd(tmp));
  ret = reader->parse(tmp, trame);
  delete reader;
  return (ret);
}

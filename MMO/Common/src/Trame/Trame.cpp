//
// Trame.cpp for  in /home/ansel_l/Documents/Pfa/work/Common/src/Trame
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:55:14 2013 laurent ansel
// Last update Mon Jan 27 09:16:27 2014 laurent ansel
//

#include		<sstream>
#include		<fstream>
#include		"Trame/Trame.hh"

Trame::Trame(bool const end):
  Json::Value(),
  _end(end),
  _size(0)
{

}

Trame::Trame(std::string const &str, bool const end):
  Json::Value(),
  _end(end),
  _size(0)
{
  Trame::toTrame(*this, str);
}

Trame::~Trame()
{

}

// Trame			&Trame::operator[](std::string const &key) const
// {
//   return ((*this)[key]);
// }

bool			Trame::toString(std::string &content) const
{
  Json::StyledWriter	*writer = new Json::StyledWriter;
  size_t		pos;
  std::string		str(CONTENT + std::string(" : "));

  content = writer->write(*this);
  delete writer;
  if ((pos = content.find(str)) != std::string::npos)
    if (pos < _size)
      content.erase(pos + std::string(str).size(), _size);
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

void			Trame::setSize(size_t const size)
{
  this->_size = size;
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

int			Trame::toTrame(Trame &trame, std::string const &str)
{
  std::string		tmp = str;
  bool			ret;
  Json::Reader		*reader = new Json::Reader;

  trame.setEnd(Trame::isEnd(tmp));
  Trame::removeTrameEnd(tmp);
  ret = reader->parse(tmp, trame);
  delete reader;
  if (!ret)
    return (-1);
  if (trame.asString().size() < str.size())
    return (1);
  return (0);
}

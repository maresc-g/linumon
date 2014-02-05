//
// Trame.cpp for  in /home/ansel_l/Documents/Pfa/work/Common/src/Trame
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Nov 28 16:55:14 2013 laurent ansel
// Last update Wed Feb  5 14:53:55 2014 laurent ansel
//

#include		<sstream>
#include		<fstream>
#include		"Trame/Trame.hh"

Trame::Trame(bool const end):
  JsonFile(),
  _end(end),
  _size(0)
{

}

Trame::Trame(std::string const &str, bool const end):
  JsonFile(),
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

Trame			&Trame::operator()(Json::Value &value) const
{
  return (*(static_cast<Trame *>(&value)));
}

Trame const		&Trame::operator()(Json::Value const &value) const
{
  return (*(static_cast<const Trame *>(&value)));
}

void			Trame::setSize(size_t const size)
{
  this->_size = size;
}

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

std::string		Trame::toString() const
{
  std::string		content;
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
  return (content);
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

int			Trame::toTrame(Trame &trame, std::string const &str)
{
  std::string		tmp = str;
  std::string		result;
  bool			ret;
  Json::Reader		*reader = new Json::Reader;

  trame.setEnd(Trame::isEnd(tmp));
  Trame::removeTrameEnd(tmp);
  ret = reader->parse(tmp, trame);
  delete reader;
  trame.toString(result);
  if (!ret)
    return (-1);
  if (result.size() < str.size())
    return (1);
  return (0);
}

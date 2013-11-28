//
// Entry.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/Server/include/FileSystem
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 14:24:48 2013 alexis mestag
// Last update Mon Nov  4 14:38:59 2013 alexis mestag
//

#include			"FileSystem/Entry.hh"

namespace			FileSystem
{
  Entry::Entry() :
    _path(""), _type(NOTYPE)
  {

  }

  Entry::Entry(std::string const &path, FileSystem::eType const type) :
    _path(path), _type(type)
  {

  }

  Entry::Entry(Entry const &rhs)
  {
    *this = rhs;
  }

  Entry::~Entry()
  {

  }

  Entry				&Entry::operator=(Entry const &rhs)
  {
    if (this != &rhs)
      {
	this->setPath(rhs.getPath());
	this->setType(rhs.getType());
      }
    return (*this);
  }

  std::string const		&Entry::getPath() const
  {
    return (_path);
  }

  void				Entry::setPath(std::string const &path)
  {
    _path = path;
  }

  FileSystem::eType		Entry::getType() const
  {
    return (_type);
  }

  void				Entry::setType(FileSystem::eType const type)
  {
    _type = type;
  }
}

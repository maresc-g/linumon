//
// File.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 14:41:24 2013 alexis mestag
// Last update Mon Nov  4 17:40:55 2013 alexis mestag
//

#include			"FileSystem/File.hh"

namespace			FileSystem
{
  File::File() :
    Entry("", eType::FILE)
  {

  }

  File::File(std::string const &path) :
    Entry(path, eType::FILE)
  {

  }

  File::File(File const &rhs) :
    Entry(rhs)
  {
    *this = rhs;
  }

  File::~File()
  {

  }

  File				&File::operator=(File const &rhs)
  {
    if (this != &rhs)
      {

      }
    return (*this);
  }
}

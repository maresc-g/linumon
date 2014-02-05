//
// ADynamicLibrary.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 21:23:06 2013 alexis mestag
// Last update Wed Feb  5 12:48:28 2014 alexis mestag
//

#include			"DynamicLibrary/ADynamicLibrary.hh"

ADynamicLibrary::ADynamicLibrary() :
  _file(new FileSystem::File(""))
{
  
}

ADynamicLibrary::ADynamicLibrary(std::string const &path) :
  _file(new FileSystem::File(path))
{

}

ADynamicLibrary::ADynamicLibrary(ADynamicLibrary const &rhs) :
  _file(new FileSystem::File(rhs.getPath()))
{
  *this = rhs;
}

ADynamicLibrary::~ADynamicLibrary()
{
  delete _file;
}

ADynamicLibrary			&ADynamicLibrary::operator=(ADynamicLibrary const &rhs)
{
  if (this != &rhs)
    {
      this->setPath(rhs.getPath());
    }
  return (*this);
}

std::string const		&ADynamicLibrary::getPath() const
{
  return (_file->getPath());
}

void				ADynamicLibrary::setPath(std::string const &path)
{
  this->unload();
  _file->setPath(path);
}

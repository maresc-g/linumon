//
// UnixDynamicLibrary.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/DynamicLibrary
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov  2 16:55:11 2013 alexis mestag
// Last update Wed Feb  5 12:48:37 2014 alexis mestag
//

#include		<iostream>
#include		<dlfcn.h>
#include		"DynamicLibrary/UnixDynamicLibrary.hh"

UnixDynamicLibrary::UnixDynamicLibrary() :
  ADynamicLibrary(""), _lib(NULL)
{

}

UnixDynamicLibrary::UnixDynamicLibrary(std::string const &path) :
  ADynamicLibrary(path), _lib(NULL)
{

}

UnixDynamicLibrary::UnixDynamicLibrary(UnixDynamicLibrary const &rhs) :
  ADynamicLibrary(rhs), _lib(NULL)
{
  *this = rhs;
}

UnixDynamicLibrary	&UnixDynamicLibrary::operator=(UnixDynamicLibrary const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

UnixDynamicLibrary::~UnixDynamicLibrary()
{
  this->unload();
}

bool			UnixDynamicLibrary::load()
{
  bool			ret = true;

  _lib = dlopen(this->getPath().c_str(), RTLD_LAZY);
  if (!_lib)
    {
      std::cerr << this->getLastError() << std::endl;
      ret = false;
    }
  return (ret);
}
bool			UnixDynamicLibrary::isLoaded() const
{
  return (_lib ? true : false);
}

void			UnixDynamicLibrary::unload()
{
  if (this->isLoaded()) {
    dlclose(_lib);
    _lib = NULL;
  }
}

void			*UnixDynamicLibrary::getSymbol(std::string const &sym)
{
  void			*symbol;

  symbol = dlsym(_lib, sym.c_str());
  if (!symbol)
    std::cerr << this->getLastError() << std::endl;
  return (symbol);
}

char			*UnixDynamicLibrary::getLastError() const
{
  return (dlerror());
}

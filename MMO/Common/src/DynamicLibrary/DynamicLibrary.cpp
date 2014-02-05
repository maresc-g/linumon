//
// DynamicLibrary.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype/Server/include/DynamicLibrary
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Nov  3 18:06:07 2013 alexis mestag
// Last update Wed Feb  5 11:22:27 2014 alexis mestag
//

#include		"DynamicLibrary/DynamicLibrary.hh"

DynamicLibrary::DynamicLibrary() :
#ifdef	_WIN32
  WindowsDynamicLibrary()
#else
  UnixDynamicLibrary()
#endif
{

}

DynamicLibrary::DynamicLibrary(std::string const &path) :
#ifdef	_WIN32
  WindowsDynamicLibrary(path)
#else
  UnixDynamicLibrary(path)
#endif
{

}

DynamicLibrary::DynamicLibrary(DynamicLibrary const &rhs) :
#ifdef	_WIN32
  WindowsDynamicLibrary(rhs)
#else
  UnixDynamicLibrary(rhs)
#endif
{
  *this = rhs;
}

DynamicLibrary::~DynamicLibrary()
{

}

DynamicLibrary		&DynamicLibrary::operator=(DynamicLibrary const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

// IDynamicLibrary		&DynamicLibrary::getDeepCopy() const
// {
//   return (*new DynamicLibrary(*this));
// }

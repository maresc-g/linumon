//
// WindowsDynamicLibrary.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype/Server/include/DynamicLibrary
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Nov  3 17:58:12 2013 alexis mestag
// Last update Tue Nov  5 08:59:11 2013 alexis mestag
//


#ifndef			__WINDOWSDYNAMICLIBRARY_HH__
# define		__WINDOWSDYNAMICLIBRARY_HH__

# ifdef _WIN32

#  include		<Windows.h>
#  include		<direct.h>
#  include		"DynamicLibrary/ADynamicLibrary.hh"

class			WindowsDynamicLibrary : public ADynamicLibrary
{
private:
  HMODULE		_lib;

protected:
  WindowsDynamicLibrary();
  WindowsDynamicLibrary(WindowsDynamicLibrary const &rhs);
  WindowsDynamicLibrary	&operator=(WindowsDynamicLibrary const &rhs);

public:
  WindowsDynamicLibrary(std::string const &path);
  virtual ~WindowsDynamicLibrary();

  virtual bool	load();
  virtual void	destroy();
  virtual void	*getSymbol(std::string const &sym);
};

# endif

#endif // !__WINDOWSDYNAMICLIBRARY_HH__

//
// UnixDynamicLibrary.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/DynamicLibrary
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov  2 16:54:11 2013 alexis mestag
// Last update Wed Feb  5 11:30:29 2014 alexis mestag
//

#ifndef			__UNIXDYNAMICLIBRARY_HH__
# define		__UNIXDYNAMICLIBRARY_HH__

# include		"DynamicLibrary/ADynamicLibrary.hh"

class			UnixDynamicLibrary : public ADynamicLibrary
{
private:
  void			*_lib;

protected:
  UnixDynamicLibrary();

private:
  char			*getLastError() const;

public:
  UnixDynamicLibrary(std::string const &path);
  UnixDynamicLibrary(UnixDynamicLibrary const &rhs);

  UnixDynamicLibrary	&operator=(UnixDynamicLibrary const &rhs);

  virtual ~UnixDynamicLibrary();

  virtual bool		load();
  virtual bool		isLoaded() const;
  virtual void		unload();
  virtual void		*getSymbol(std::string const &obj);
};

#endif

//
// IDynamicLibrary.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype/Server/include/DynamicLibrary
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov  2 16:41:20 2013 alexis mestag
// Last update Wed Feb  5 11:29:06 2014 alexis mestag
//

#ifndef			__IDYNAMICLIBRARY_HH__
# define		__IDYNAMICLIBRARY_HH__

# include		<string>

class			IDynamicLibrary
{
public:
  virtual ~IDynamicLibrary() {}

  virtual bool			load() = 0;
  virtual bool			isLoaded() const = 0;
  virtual void			unload() = 0;

  virtual void			*getSymbol(std::string const &symbol) = 0;
  virtual std::string const	&getPath() const = 0;
  virtual void			setPath(std::string const &path) = 0;
};

#endif

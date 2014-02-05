//
// ADynamicLibrary.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 21:20:25 2013 alexis mestag
// Last update Wed Feb  5 12:35:25 2014 alexis mestag
//

#ifndef			__ADYNAMICLIBRARY_HH__
# define		__ADYNAMICLIBRARY_HH__

# include		"DynamicLibrary/IDynamicLibrary.hh"
# include		"FileSystem/File.hh"

class			ADynamicLibrary : public IDynamicLibrary
{
private:
  FileSystem::File		*_file;

protected:
  ADynamicLibrary();

public:
  ADynamicLibrary(std::string const &path);
  ADynamicLibrary(ADynamicLibrary const &rhs);

  ADynamicLibrary	&operator=(ADynamicLibrary const &rhs);

  virtual ~ADynamicLibrary();

  virtual std::string const	&getPath() const;
  virtual void			setPath(std::string const &path);
};

#endif

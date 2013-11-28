//
// Entry.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/Server/include/FileSystem
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 14:19:17 2013 alexis mestag
// Last update Mon Nov  4 17:39:09 2013 alexis mestag
//

#ifndef			__FILESYSTEM_ENTRY_HH__
# define		__FILESYSTEM_ENTRY_HH__

# include		<string>

namespace		FileSystem
{
  enum			eType
    {
      NOTYPE,
      UNKNOWN,
      DIRECTORY,
      FILE
    };

  class			Entry
  {
  private:
    std::string		_path;
    FileSystem::eType	_type;

    Entry();

    void		setPath(std::string const &path);
    void		setType(FileSystem::eType const type);

  public:
    Entry(std::string const &path, FileSystem::eType const type);
    Entry(Entry const &rhs);
    virtual ~Entry();

    Entry		&operator=(Entry const &rhs);

    std::string const	&getPath() const;
    FileSystem::eType	getType() const;
  };
}

#endif

//
// Directory.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 15:01:33 2013 alexis mestag
// Last update Mon Nov 25 21:00:25 2013 alexis mestag
//

#ifndef			__FILESYSTEM_DIRECTORY_HH__
# define		__FILESYSTEM_DIRECTORY_HH__

# include		<list>
# include		"FileSystem/Entry.hh"

namespace		FileSystem
{
  class			Directory : public Entry
  {
  private:
    std::list<Entry *>	*_entries;

  private:
    Directory();

    void			setEntries(std::list<Entry *> &entries);
    void			deleteEntries();

  public:
    Directory(std::string const &path);
    Directory(Directory const &rhs);
    virtual ~Directory();

    Directory			&operator=(Directory const &rhs);

    void			updateEntries();
    std::list<Entry *> const	&getEntries() const;
    std::list<Entry *>		&getEntriesDeepCopy() const;
  };
}

#endif

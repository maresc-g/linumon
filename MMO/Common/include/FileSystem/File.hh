//
// File.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 14:41:39 2013 alexis mestag
// Last update Mon Nov  4 15:03:01 2013 alexis mestag
//

#ifndef			__FILESYSTEM_FILE_HH__
# define		__FILESYSTEM_FILE_HH__

#include		"FileSystem/Entry.hh"

namespace		FileSystem
{
  class			File : public Entry
  {
  private:
    File();

  public:
    File(std::string const &path);
    File(File const &rhs);
    virtual ~File();

    File		&operator=(File const &rhs);
  };
}

#endif

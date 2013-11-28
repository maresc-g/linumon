//
// Directory.cpp for RType in /home/mestag_a/Documents/Projets/Tek3/RType
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 14:58:59 2013 alexis mestag
// Last update Mon Nov 25 21:02:34 2013 alexis mestag
//

#ifndef	_WIN32
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
#else
# include <Windows.h>
#endif

#include			"FileSystem/Directory.hh"
#include			"FileSystem/File.hh"

namespace			FileSystem
{
  Directory::Directory() :
    Entry("", eType::DIRECTORY), _entries(NULL)
  {

  }

  Directory::Directory(std::string const &path) :
    Entry(path, eType::DIRECTORY), _entries(NULL)
  {

  }

  Directory::Directory(Directory const &rhs) :
    Entry(rhs), _entries(NULL)
  {
    *this = rhs;
  }

  Directory::~Directory()
  {
    this->deleteEntries();
  }

  Directory			&Directory::operator=(Directory const &rhs)
  {
    if (this != &rhs)
      {
	this->setEntries(rhs.getEntriesDeepCopy());
      }
    return (*this);
  }

  void				Directory::setEntries(std::list<Entry *> &entries)
  {
    this->deleteEntries();
    _entries = &entries;
  }

#ifndef	_WIN32
  void				Directory::updateEntries()
  {
    std::string			fullPath;
    DIR				*dirp;
    struct dirent		*dirpEntry;
    struct stat			st;
    FileSystem::Entry		*entry;

    this->deleteEntries();
    _entries = new std::list<Entry *>;
    dirp = opendir(this->getPath().c_str());
    if (dirp)
      {
	while ((dirpEntry = readdir(dirp)))
	  {
	    fullPath = this->getPath() + "/" + dirpEntry->d_name;
	    if (stat(fullPath.c_str(), &st) != -1)
	      {
		entry = NULL;
		if (S_ISDIR(st.st_mode))
		  entry = new FileSystem::Directory(fullPath);
		else if (S_ISREG(st.st_mode))
		  entry = new FileSystem::File(fullPath);
		else
		  entry = new FileSystem::Entry(fullPath, eType::UNKNOWN);
		_entries->push_back(entry);
	      }
	  }
	closedir(dirp);
      }
  }
#else
  void				Directory::updateEntries()
  {
    HANDLE			dirp;
    WIN32_FIND_DATA		dirpEntry;
    std::string			fullPath;
    Entry			*entry;

    this->deleteEntries();
    _entries = new std::list<Entry *>;
    if ((dirp = FindFirstFile((this->getPath() + "/*").c_str(), &dirpEntry)) != INVALID_HANDLE_VALUE)
      {
	do
	  {
	    fullPath = this->getPath() + "/" + dirpEntry.cFileName;
	    if (dirpEntry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	      entry = new FileSystem::Directory(fullPath);
	    else if (dirpEntry.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
	      entry = new FileSystem::File(fullPath);
	    else
	      entry = new FileSystem::Entry(fullPath, eType::UNKNOWN);
	    _entries->push_back(entry);
	  } while (FindNextFile(dirp, &dirpEntry));
	FindClose(dirp);
      }
  }
#endif

  std::list<Entry *> const	&Directory::getEntries() const
  {
    return (*_entries);
  }

  std::list<Entry *>		&Directory::getEntriesDeepCopy() const
  {
    std::list<Entry *>		*ret = new std::list<Entry *>;

    for (auto it = _entries->begin() ; it != _entries->end() ; ++it)
      ret->push_back(new Entry(**it));
    return (*ret);
  }

  static bool			deleteEntryPointer(Entry *entry)
  {
    delete entry;
    return (true);
  }

  void				Directory::deleteEntries()
  {
    if (_entries)
      {
	_entries->remove_if(&deleteEntryPointer);
	delete _entries;
	_entries = NULL;
      }
  }
}

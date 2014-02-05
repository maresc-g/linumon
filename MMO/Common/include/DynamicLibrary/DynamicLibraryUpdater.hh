//
// DynamicLibraryUpdater.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/rtype/rtype
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov  4 20:06:17 2013 alexis mestag
// Last update Wed Nov 13 13:27:03 2013 alexis mestag
//

#ifndef			__DYNAMICLIBRARYUPDATER_HH__
# define		__DYNAMICLIBRARYUPDATER_HH__

# include		<string>
# include		"Thread/Thread.hpp"
# include		"Mutex/Mutex.hpp"
# include		"FileSystem/Directory.hh"
# include		"Inotify/Inotify.hpp"

# define		LIB_PATH	"Libraries"

class			DynamicLibraryUpdater : public Thread
{
private:
  FileSystem::Directory	*_directory;
  Inotify		*_inotify;
  IMutex		*_mtx;
  bool			_canUpdate;

  DynamicLibraryUpdater(DynamicLibraryUpdater const &rhs);
  DynamicLibraryUpdater	&operator=(DynamicLibraryUpdater const &rhs);

public:
  DynamicLibraryUpdater(std::string const &path = LIB_PATH);
  virtual ~DynamicLibraryUpdater();

  void			startUpdate();
  void			stopUpdate();
  void			updateLibraries();
  FileSystem::Directory const	&getDirectory() const;
  Inotify		&getInotify();

  void			setCanUpdate(bool const canUpdate);
  bool			getCanUpdate() const;
};

#endif

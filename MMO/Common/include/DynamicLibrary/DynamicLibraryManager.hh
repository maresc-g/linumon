//
// DynamicLibraryManager.hh for RType in /home/mestag_a/Documents/Projets/Tek3/RType/Server
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Nov  3 18:41:29 2013 alexis mestag
// Last update Sun Nov 24 22:51:04 2013 alexis mestag
//

#ifndef			__DYNAMICLIBRARYMANAGER_HH__
# define		__DYNAMICLIBRARYMANAGER_HH__

# include		<string>
# include		"DynamicLibrary/DynamicLibraryUpdater.hh"
# include		"DynamicLibrary/IDynamicLibrary.hh"
# include		"GameLoop/GameLibraries.hh"
# include		"Utility/Singleton.hpp"
# include		"Mutex/Mutex.hpp"

class			DynamicLibraryManager : public Singleton<DynamicLibraryManager>
{
private:
  DynamicLibraryUpdater	*_updater;
  GameLibraries		*_libraries;
  IMutex		*_mtx;

  DynamicLibraryManager(DynamicLibraryManager const &rhs);
  DynamicLibraryManager	&operator=(DynamicLibraryManager const &rhs);

public:
  DynamicLibraryManager();
  virtual ~DynamicLibraryManager();

  GameLibraries		&getGameLibrariesCopy() const;
  void			setLibrary(IDynamicLibrary &lib, bool const lock = true);

  void			resetLibraries(std::list<FileSystem::Entry *> const *entries);
};

#endif

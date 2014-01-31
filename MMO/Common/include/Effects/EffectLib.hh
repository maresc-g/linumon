//
// EffectLib.hh for EffectLib in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jan 30 12:30:55 2014 alexis mestag
// Last update Fri Jan 31 11:10:51 2014 alexis mestag
//

#ifndef				__EFFECTLIB_HH__
# define			__EFFECTLIB_HH__

# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"FileSystem/File.hh"

class				EffectLib : public Persistent, public Nameable
{
  friend class			odb::access;

public:
  FileSystem::File		*_file;

private:
  EffectLib();
  EffectLib(std::string const &name, std::string const &path);

public:
  EffectLib(EffectLib const &rhs);
  virtual ~EffectLib();

  EffectLib			&operator=(EffectLib const &rhs);

  FileSystem::File const	&getFile() const;
  void				setFile(FileSystem::File const &file);
};

# ifdef	ODB_COMPILER
#  pragma db object(EffectLib)
#  pragma db member(EffectLib::_file) transient
#  pragma db member(EffectLib::_path) virtual(std::string) get(_file->getPath()) set(_file->setPath(?))
# endif

#endif

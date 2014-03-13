//
// EffectLib.hh for EffectLib in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jan 30 12:30:55 2014 alexis mestag
// Last update Wed Mar 12 14:13:50 2014 alexis mestag
//

#ifndef				__EFFECTLIB_HH__
# define			__EFFECTLIB_HH__

# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"Effects/IEffect.hpp"
# include			"DynamicLibrary/DynamicLibrary.hh"
# include			"Utility/ISerialization.hh"

class				EffectLib : public Persistent, public Nameable, public ISerialization
{
  friend class			odb::access;

public:
  IDynamicLibrary		*_dl;

private:
  EffectLib();

public:
  EffectLib(std::string const &name, std::string const &path);
  EffectLib(EffectLib const &rhs);
  virtual ~EffectLib();

  EffectLib			&operator=(EffectLib const &rhs);

  std::string const		&getPath() const;
  void				setPath(std::string const &path);

  IEffect			*getEffect() const;

  virtual bool			serialization(Trame &trame) const;
  static EffectLib		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(EffectLib)
#  pragma db member(EffectLib::_dl) transient
#  pragma db member(EffectLib::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(EffectLib::_path) virtual(std::string) get(getPath()) set(setPath(?))
# endif

#endif

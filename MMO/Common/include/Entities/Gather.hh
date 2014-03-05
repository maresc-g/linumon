//
// Gather.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:25 2014 laurent ansel
// Last update Mon Mar  3 22:01:18 2014 alexis mestag
//

#ifndef			__GATHER_HH__
# define 		__GATHER_HH__

#include		"Database/Persistent.hh"
#include		"Entities/AItem.hh"
#include		"Entities/Level.hh"
#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Ressource.hh"

class			Gather : public ISerialization
{
  friend class		odb::access;

private:
  Level			*_level;
  Ressource const	*_ressource;

  Gather();

  void			setLevelObject(Level const &level);
  void			setRessource(Ressource const &item);

public:
  Gather(Gather const &rhs);
  virtual ~Gather();

  Gather		&operator=(Gather const &rhs);

  Level const		&getLevelObject() const;
  Ressource const	&getRessource() const;

  Level::type		getLevel() const;
  void			setLevel(Level::type const level);

  Level::type		getExp() const;
  void			setExp(Level::type const exp);

  virtual bool		serialization(Trame &trame) const;
  static Gather		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db value(Gather)
#  pragma db member(Gather::_level) transient
#  pragma db member(Gather::_ressource)
#  pragma db member(Gather::level) virtual(Level::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Gather::exp) virtual(Level::type) get(getExp()) set(setExp(?))
# endif

#endif

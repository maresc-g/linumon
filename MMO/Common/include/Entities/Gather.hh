//
// Gather.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:25 2014 laurent ansel
// Last update Tue Mar 18 23:47:45 2014 alexis mestag
//

#ifndef			__GATHER_HH__
# define 		__GATHER_HH__

#include		"Database/Persistent.hh"
#include		"Entities/AItem.hh"
#include		"Entities/Levelable.hh"
#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"
#include		"Entities/Ressource.hh"

class			Gather : public ISerialization
{
  friend class		odb::access;

private:
  Levelable::type	_level;
  Levelable::type	_exp;
  Ressource const	*_ressource;

private:
  Gather();

  void			setRessource(Ressource const &item);

public:
  Gather(Gather const &rhs);
  virtual ~Gather();

  Gather		&operator=(Gather const &rhs);

  Ressource const	&getRessource() const;

  Levelable::type		getLevel() const;
  void			setLevel(Levelable::type const level);

  Levelable::type		getExp() const;
  void			setExp(Levelable::type const exp);

  virtual bool		serialization(Trame &trame) const;
  static Gather		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db value(Gather)
#  pragma db member(Gather::_level) transient
#  pragma db member(Gather::_exp) transient
#  pragma db member(Gather::_ressource) not_null
#  pragma db member(Gather::level) virtual(Levelable::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Gather::exp) virtual(Levelable::type) get(getExp()) set(setExp(?))
# endif

#endif

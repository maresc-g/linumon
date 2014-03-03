//
// Gather.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 28 15:08:25 2014 laurent ansel
// Last update Fri Feb 28 15:19:06 2014 laurent ansel
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
  Level			_level;
  Ressource const	*_ressource;

  Gather();

  void			setLevel(Level const &level);
  void			setRessource(Ressource const &item);

public:
  Gather(Gather const &rhs);
  virtual ~Gather();

  Gather				&operator=(Gather const &rhs);

  Level const			&getLevel() const;
  Ressource const		&getRessource() const;

  virtual bool		serialization(Trame &trame) const;
  static Gather		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db value(Gather)
# endif

#endif

//
// Spells.hh for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:33:20 2014 alexis mestag
// Last update Fri Jan 24 21:12:20 2014 alexis mestag
//

#ifndef			__SPELLS_HH__
# define		__SPELLS_HH__

# include		"Entities/Spell.hh"

class			Spells
{
  friend class		odb::access;

public:
  typedef std::list<Spell const *>	containerType;

private:
  containerType		_spells;

private:
  Spells(Spells const &rhs);

  Spells		&operator=(Spells const &rhs);

public:
  Spells();
  virtual ~Spells();

  containerType const	&getContainer() const;
};

# ifdef	ODB_COMPILER
#  pragma db value(Spells)
# endif

#endif

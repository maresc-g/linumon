//
// Spells.hh for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:33:20 2014 alexis mestag
// Last update Fri Feb  7 12:56:27 2014 laurent ansel
//

#ifndef			__SPELLS_HH__
# define		__SPELLS_HH__

# include		"Entities/Spell.hh"
# include		"Utility/ISerialization.hh"

class			Spells : public ISerialization
{
  friend class		odb::access;

public:
  typedef std::list<Spell const *>	containerType;

private:
  containerType		_spells;

private:
  Spells(Spells const &rhs);

  void			addSpell(Spell const &spell);

public:
  Spells();
  virtual ~Spells();

  Spells		&operator=(Spells const &rhs);

  containerType const	&getContainer() const;

  virtual bool		serialization(Trame &trame) const;
  static Spells		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Spells)
# endif

#endif

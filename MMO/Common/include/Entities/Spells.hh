//
// Spells.hh for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:33:20 2014 alexis mestag
// Last update Fri Mar 14 21:09:54 2014 laurent ansel
//

#ifndef			__SPELLS_HH__
# define		__SPELLS_HH__

# include		"Database/Persistent.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Wrapper.hpp"

class			Spell;

class			Spells : public ISerialization, public ContainerWrapper<std::list<Spell const *>>
{
private:
  void			addSpell(Spell const &spell);
  void			addSpell(Spell *spell);

public:
  Spells();
  Spells(Spells const &rhs);

  virtual ~Spells();

  Spells		&operator=(Spells const &rhs);

  virtual bool		serialization(Trame &trame) const;
  static Spells		*deserialization(Trame const &trame);
};

# include		"Entities/Spell.hh"

#endif

//
// SpellContainer.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Mar  7 11:30:49 2014 guillaume marescaux
// Last update Fri Mar  7 12:33:57 2014 guillaume marescaux
//

#ifndef 		__SPELLCONTAINER_HH__
# define 		__SPELLCONTAINER_HH__

#include		"Entities/Spell.hh"

class			SpellContainer
{
private:

  unsigned int		_target;
  unsigned int		_launcher;
  Spell			*_spell;

public:

  SpellContainer(unsigned int target, unsigned int launcher, Spell *spell);
  virtual ~SpellContainer();

public:

  unsigned int		getTarget(void) const;
  unsigned int		getLauncher(void) const;
  Spell const		&getSpell(void) const;
};

#endif

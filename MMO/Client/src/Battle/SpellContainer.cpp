//
// SpellContainer.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Mar  7 11:36:05 2014 guillaume marescaux
// Last update Tue Mar 11 12:38:46 2014 cyril jourdain
//

#include			"Battle/SpellContainer.hh"

SpellContainer::SpellContainer(unsigned int target, unsigned int launcher, Spell *spell):
  _target(target), _launcher(launcher), _spell(spell)
{
}

SpellContainer::~SpellContainer()
{
}

unsigned int			SpellContainer::getTarget() const { return (_target); }
unsigned int			SpellContainer::getLauncher() const { return (_launcher); }
Spell const			&SpellContainer::getSpell() const { return (*_spell); }

//
// SpellLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Mar  8 16:00:03 2014 laurent ansel
// Last update Sat Mar  8 16:10:09 2014 laurent ansel
//

#ifndef 			__SPELLLOADER_HH__
# define 			__SPELLLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Spell.hh"

class				SpellsList
{
public:
  typedef Spell		value;

private:
  void				setSpellsList(std::list<Spell *> const &spellsList);

private:
  std::list<Spell *>		*_spellsList;

public:
  SpellsList();
  virtual ~SpellsList();

  std::list<Spell *> const	&getSpellsList() const;

  void				addSpell(Spell *spell);

  Spell				*getSpell(std::string const &name) const;
  Spell				*getSpell(unsigned int const id) const;
};

class				SpellLoader : public ILoader<SpellsList>
{
private:
  SpellsList			*_spellsList;
public:
  SpellLoader();
  virtual ~SpellLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual SpellsList const	&getLoaderContent() const;
  virtual SpellsList::value	*getValue(std::string const &name) const;
  virtual SpellsList::value	*getValue(unsigned int const id) const;
};

#endif

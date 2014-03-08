//
// SpellLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Mar  8 16:02:52 2014 laurent ansel
// Last update Sat Mar  8 16:11:23 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
#include			"Entities/Spell-odb.hxx"
#endif
#include			"Database/Repositories/Repository.hpp"
#include			"Loader/SpellLoader.hh"

/*
**
**	SpellsList
**
*/

SpellsList::SpellsList() :
  _spellsList(new std::list<Spell *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Spell>		*mm = &Database::getRepository<Spell>();

  *_spellsList = mm->getAll();
#endif
}

SpellsList::~SpellsList()
{
  for (auto it = _spellsList->begin() ; it != _spellsList->end() ; ++it)
    delete *it;
  delete _spellsList;
}

std::list<Spell *> const	&SpellsList::getSpellsList() const
{
  return (*this->_spellsList);
}

void				SpellsList::addSpell(Spell *spell)
{
  this->_spellsList->push_back(spell);
}

Spell				*SpellsList::getSpell(std::string const &name) const
{
  for (auto it = _spellsList->begin() ; it != _spellsList->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Spell				*SpellsList::getSpell(unsigned int const) const
{
  return (NULL);
}

/*
**
**	SpellLoader
**
*/

SpellLoader::SpellLoader() :
  _spellsList(new SpellsList)
{

}

SpellLoader::~SpellLoader()
{
  delete _spellsList;
}

bool				SpellLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["SPELLSLIST"];
  for (auto it = _spellsList->getSpellsList().begin() ; it != _spellsList->getSpellsList().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["SPELLSLIST"][(*it)->getName()]));
  return (ret);
}

bool				SpellLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Spell			*spell;

  if (trame[CONTENT].isMember("SPELLSLIST"))
    {
      auto			members = trame[CONTENT]["SPELLSLIST"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  spell = Spell::deserialization(trame(trame[CONTENT]["SPELLSLIST"][*it]));
	  if (spell)
	    {
	      spell->setName(*it);
	      _spellsList->addSpell(spell);
	    }
	}
    }
  return (ret);
}

SpellsList const			&SpellLoader::getLoaderContent() const
{
  return (*_spellsList);
}

SpellsList::value			*SpellLoader::getValue(std::string const &name) const
{
  return (this->_spellsList->getSpell(name));
}

SpellsList::value			*SpellLoader::getValue(unsigned int const id) const
{
  return (this->_spellsList->getSpell(id));
}

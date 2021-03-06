//
// Spells.cpp for Spells in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Utility
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 20:54:19 2014 alexis mestag
// Last update Fri Mar 21 00:18:02 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Spells.hh"
#include			"Loader/LoaderManager.hh"

Spells::Spells() :
  ContainerWrapper<container_type>()
{

}

Spells::Spells(Spells const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Spells::~Spells()
{

}

Spells				&Spells::operator=(Spells const &rhs)
{
  if (this != &rhs)
    {
      this->setContainer(rhs.getContainer());
    }
  return (*this);
}

void				Spells::addSpell(Spell const &spell)
{
  this->getContainer().push_back(&spell);
}

void				Spells::addSpell(Spell *spell)
{
  this->getContainer().push_back(spell);
}

bool				Spells::serialization(Trame &trame) const
{
  bool				ret = true;
  // std::ostringstream		str;
  // unsigned int			nb = 0;

  for (auto it = this->begin() ; it != this->end() && ret; ++it)
    {
      // str << nb;
      //      (*it)->serialization(trame(trame["SPS"]));
      // str.str("");
      // nb++;
      trame["SPS"][(*it)->getName()];
    }
  return (ret);
}

Spells				*Spells::deserialization(Trame const &trame)
{
  Spells			*spells = NULL;
  Spell				*spell = NULL;

  if (trame.isMember("SPS"))
    {
      auto			members = trame["SPS"].getMemberNames();

      spells = new Spells;
      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  // spell = Spell::deserialization(trame(trame["SPS"][*it]));
	  // if (spell)
	  //   {
	  //     spell->setName(*it);
	  //     spells->addSpell(*spell);
	  //   }
	  spell = (**LoaderManager::getInstance()->getSpellLoader())->getValue(*it);
	  if (spell)
	    {
	      std::cout << "NAME = " << spell->getName() << std::endl;
	      spells->addSpell(spell);
	    }
	}
    }
  // std::cerr << "\tSpells deserialization, returning : " << spells << std::endl;
  return (spells);
}

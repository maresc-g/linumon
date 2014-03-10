//
// PNJLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar  7 14:18:01 2014 laurent ansel
// Last update Fri Mar  7 14:47:29 2014 laurent ansel
//

#ifndef 			__HEALLOADER_HH__
# define 			__HEALLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Heal.hh"

class				Heals
{
public:
  typedef Heal			value;

private:
  void				setHeals(std::list<Heal *> const &heals);

private:
  std::list<Heal *>		*_heals;

public:
  Heals();
  virtual ~Heals();

  std::list<Heal *> const	&getHeals() const;

  void				addHeal(Heal *heal);

  Heal				*getHeal(std::string const &name) const;
  Heal				*getHeal(unsigned int const id) const;
};

class				HealLoader : public ILoader<Heals>
{
private:
  Heals				*_heals;
public:
  HealLoader();
  virtual ~HealLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual Heals const		&getLoaderContent() const;
  virtual Heals::value		*getValue(std::string const &name) const;
  virtual Heals::value		*getValue(unsigned int const id) const;
};

#endif

//
// ConsumableLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 11:55:17 2014 laurent ansel
// Last update Fri Mar  7 14:18:51 2014 laurent ansel
//

#ifndef 			__CONSUMABLELOADER_HH__
# define 			__CONSUMABLELOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Consumable.hh"

class				Consumables
{
public:
  typedef Consumable		value;

private:
  void				setConsumables(std::list<Consumable *> const &consumables);

private:
  std::list<Consumable *>	*_consumables;

public:
  Consumables();
  virtual ~Consumables();

  std::list<Consumable *> const	&getConsumables() const;

  void				addConsumable(Consumable *consumable);

  Consumable			*getConsumable(std::string const &name) const;
  Consumable			*getConsumable(unsigned int const id) const;
};

class				ConsumableLoader : public ILoader<Consumables>
{
private:
  Consumables			*_consumables;
public:
  ConsumableLoader();
  virtual ~ConsumableLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual Consumables const	&getLoaderContent() const;
  virtual Consumables::value	*getValue(std::string const &name) const;
  virtual Consumables::value	*getValue(unsigned int const id) const;
};

#endif

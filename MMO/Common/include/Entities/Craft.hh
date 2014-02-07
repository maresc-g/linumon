//
// Craft.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:27:32 2014 laurent ansel
// Last update Fri Feb  7 14:41:30 2014 laurent ansel
//

#ifndef 		__CRAFT_HH__
# define		__CRAFT_HH__

#include		"Database/Persistent.hh"
#include		"Entities/AItem.hh"
#include		"Entities/Level.hh"
#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"

class			Craft : public ISerialization, public Nameable, public Persistent
{
  friend class		odb::access;

private:
  Level			_level;
  AItem			*_result;
  std::list<AItem *>	_ingredients;

  Craft();

  void			setLevel(Level const &level);
  void			setResult(AItem const &item);
  void			setIngredients(std::list<AItem *> const &items);

public:
  Craft(Craft const &rhs);
  Craft			&operator=(Craft const &rhs);

  virtual ~Craft();

  Level const		&getLevel() const;
  AItem const		&getResult() const;
  std::list<AItem *> const	&getIngredients() const;

  virtual bool		serialization(Trame &trame) const;
  static Craft		*deserialization(Trame const &trame);
};

#endif

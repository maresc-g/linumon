//
// Craft.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:27:32 2014 laurent ansel
// Last update Mon Feb 10 11:15:47 2014 alexis mestag
//

#ifndef 		__CRAFT_HH__
# define		__CRAFT_HH__

#include		"Database/Persistent.hh"
#include		"Entities/AItem.hh"
#include		"Entities/Level.hh"
#include		"Utility/ISerialization.hh"
#include		"Utility/Nameable.hh"

class			Craft : public Persistent, public Nameable, public ISerialization
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
  virtual ~Craft();

  Craft				&operator=(Craft const &rhs);

  Level const			&getLevel() const;
  AItem const			&getResult() const;
  std::list<AItem *> const	&getIngredients() const;

  virtual bool		serialization(Trame &trame) const;
  static Craft		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Craft)
#  pragma db member(Craft::_result) transient
#  pragma db member(Craft::_ingredients) transient
# endif

#endif

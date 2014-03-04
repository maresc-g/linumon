//
// Craft.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:27:32 2014 laurent ansel
// Last update Mon Mar  3 21:24:33 2014 alexis mestag
//

#ifndef 		__CRAFT_HH__
# define		__CRAFT_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Entities/Level.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/Wrapper.hpp"

typedef std::pair<AItem *, unsigned int>	itemStack;

class			Craft : public ISerialization, public Persistent, public Nameable,
				public ContainerWrapper<std::list<itemStack>>
{
  friend class		odb::access;

private:
  Level			*_level;
  AItem const		*_result;

  Craft();

  void			setLevelObject(Level const &level);
  void			setResult(AItem const &item);
  void			setIngredients(container_type const &items);

public:
  Craft(Craft const &rhs);
  virtual ~Craft();

  Craft			&operator=(Craft const &rhs);

  Level const		&getLevelObject() const;

  Level::type		getLevel() const;
  void			setLevel(Level::type const level);

  Level::type		getExp() const;
  void			setExp(Level::type const exp);

  AItem const		&getResult() const;
  container_type const	&getIngredients() const;

  virtual bool		serialization(Trame &trame) const;
  static Craft		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Craft)
#  pragma db member(Craft::_level) transient
#  pragma db member(Craft::_result) transient
#  pragma db member(Craft::level) virtual(Level::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Craft::exp) virtual(Level::type) get(getExp()) set(setExp(?))
# endif

#endif

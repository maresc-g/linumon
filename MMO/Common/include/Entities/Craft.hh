//
// Craft.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:27:32 2014 laurent ansel
// Last update Wed Mar 12 22:59:47 2014 laurent ansel
//

#ifndef 		__CRAFT_HH__
# define		__CRAFT_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Entities/Level.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/Wrapper.hpp"
# include		"Entities/Stack.hh"

// typedef std::pair<AItem *, unsigned int>	itemStack;

class			Craft : public ISerialization, public Persistent, public Nameable,
				public ContainerWrapper<std::list<Stack *> >
{
  friend class		odb::access;

private:
  Level			*_level;
  //  AItem const		*_result;
  Stack const		*_result;

  Craft();

  void			setLevelObject(Level const &level);
  void			setResult(Stack const &item);
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

  Stack const		&getResult() const;
  container_type const	&getIngredients() const;

  virtual bool		serialization(Trame &trame) const;
  static Craft		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Craft)
#  pragma db member(Craft::_level) transient
#  pragma db member(Craft::_result) transient
#  pragma db member(Craft::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Craft::level) virtual(Level::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Craft::exp) virtual(Level::type) get(getExp()) set(setExp(?))
# endif

#endif

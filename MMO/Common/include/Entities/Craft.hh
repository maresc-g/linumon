//
// Craft.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:27:32 2014 laurent ansel
// Last update Tue Mar 18 23:47:38 2014 alexis mestag
//

#ifndef 		__CRAFT_HH__
# define		__CRAFT_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Entities/Levelable.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/Wrapper.hpp"

// typedef std::pair<AItem *, unsigned int>	itemStack;

template <typename T>
class			Stack;

class			Craft : public ISerialization, public Persistent, public Nameable,
				public ContainerWrapper<std::list<Stack<AItem> *> >
{
  friend class		odb::access;

private:
  Levelable::type	_level;
  Levelable::type	_exp;
  Stack<AItem> const	*_result;

  Craft();

  void			setResult(Stack<AItem> const &item);
  void			setIngredients(container_type const &items);

public:
  Craft(Craft const &rhs);
  virtual ~Craft();

  Craft			&operator=(Craft const &rhs);

  Levelable::type		getLevel() const;
  void			setLevel(Levelable::type const level);

  Levelable::type		getExp() const;
  void			setExp(Levelable::type const exp);

  Stack<AItem> const	&getResult() const;
  container_type const	&getIngredients() const;

  virtual bool		serialization(Trame &trame) const;
  static Craft		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Craft)
#  pragma db member(Craft::_level) transient
#  pragma db member(Craft::_exp) transient
#  pragma db member(Craft::_result) transient
#  pragma db member(Craft::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Craft::level) virtual(Levelable::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Craft::exp) virtual(Levelable::type) get(getExp()) set(setExp(?))
# endif

# include		"Entities/Stack.hh"

#endif

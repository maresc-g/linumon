//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Feb 11 16:07:26 2014 alexis mestag
//

#ifndef 		__CONSUMABLE_HH__
# define 		__CONSUMABLE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"

class			Consumable : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef enum		eConsumable
    {
      NONE,
      VITA
    }			eConsumable;
private:
  eConsumable		_consumableType;

protected:
  Consumable();
  Consumable(std::string const &name, eConsumable const consumableType);
  Consumable(Consumable const &rhs);

  Consumable		&operator=(Consumable const &rhs);

  Consumable::eConsumable	getConsumableType() const;
  void			setConsumableType(eConsumable const consumableType);

public:
  virtual ~Consumable();

  virtual bool		serialization(Trame &trame) const;
  static Consumable	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Consumable)
#  pragma db member(Consumable::_consumableType) transient
# endif

#endif

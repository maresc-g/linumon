//
// Inventory.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:15:58 2014 laurent ansel
// Last update Mon Feb 10 13:13:13 2014 alexis mestag
//

#ifndef 			__INVENTORY_HH__
# define 			__INVENTORY_HH__

#include			<list>
#include			"Utility/ISerialization.hh"
#include			"Entities/AItem.hh"

class				Inventory : public ISerialization
{
  friend class		odb::access;

private:
  std::list<AItem *>		_inventory;
  unsigned int			_money;
  unsigned int			_limit;

  Inventory();

public:
  Inventory(Inventory const &rhs);
  virtual ~Inventory();

  Inventory			&operator=(Inventory const &rhs);

  std::list<AItem *> const	&getInventory() const;
  void				setInventory(std::list<AItem *> const &inventory);

  unsigned int			getMoney() const;
  void				setMoney(unsigned int const money);

  unsigned int			getLimit() const;
  void				setLimit(unsigned int const limit);

  virtual bool			serialization(Trame &trame) const;
  static Inventory		*deserializtion(Trame const &trame);
};

#endif

//
// Inventory.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:15:58 2014 laurent ansel
// Last update Thu Feb 27 13:49:59 2014 laurent ansel
//

#ifndef 			__INVENTORY_HH__
# define 			__INVENTORY_HH__

#include			<list>
#include			"Utility/ISerialization.hh"
#include			"Entities/AItem.hh"
#include			"Database/Persistent.hh"
#include			"JsonFile/JsonFile.hh"

class				Inventory : public Persistent, public ISerialization
{
private:
  std::string			_path;
  unsigned int			_money;
  unsigned int			_limit;
  std::list<std::pair<AItem *, unsigned int> >	*_inventory;

  void				loadInventory();

public:
  Inventory();
  Inventory(Inventory const &rhs);
  virtual ~Inventory();

  Inventory			&operator=(Inventory const &rhs);

  void				serializationInventory();

  std::string const		&getPath() const;
  void				setPath(std::string const &path);

  std::list<std::pair<AItem *, unsigned int> > const	&getInventory() const;
  void				setInventory(std::list<std::pair<AItem *, unsigned int> > *inventory);

  unsigned int			getMoney() const;
  void				setMoney(unsigned int const money);
  void				addMoney(int const money);

  unsigned int			getLimit() const;
  void				setLimit(unsigned int const limit);

  void				deleteItem(unsigned int const id);
  void				addItem(AItem *item);

  AItem				*getItem(unsigned int const id) const;
  AItem				*getAndDeleteItem(unsigned int const id) const;

  unsigned int			getIdItem(std::string const &name) const;

  virtual bool			serialization(Trame &trame) const;
  static Inventory		*deserialization(Trame const &trame);
};

// # ifdef	ODB_COMPILER
// #  pragma db object(Inventory) session(false)
// #  pragma db member(Inventory::_path) get(getPath()) set(setPath(?))
// #  pragma db member(Inventory::_money) get(getMoney()) set(setMoney(?))
// #  pragma db member(Inventory::_limit) get(getLimit()) set(setLimit(?))
// #  pragma db member(Inventory::_inventory) transient
// # endif

#endif

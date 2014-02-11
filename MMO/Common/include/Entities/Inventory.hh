//
// Inventory.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:15:58 2014 laurent ansel
// Last update Tue Feb 11 16:14:38 2014 laurent ansel
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
  friend class			odb::access;

private:
  std::string			_path;
  unsigned int			_money;
  unsigned int			_limit;
  std::list<AItem *>		*_inventory;

  Inventory();
  void				loadInventory();

public:
  Inventory(Inventory const &rhs);
  virtual ~Inventory();

  Inventory			&operator=(Inventory const &rhs);

  void				serializationInventory();

  std::string const		&getPath() const;
  void				setPath(std::string const &path);

  std::list<AItem *> const	&getInventory() const;
  void				setInventory(std::list<AItem *> *inventory);

  unsigned int			getMoney() const;
  void				setMoney(unsigned int const money);

  unsigned int			getLimit() const;
  void				setLimit(unsigned int const limit);

  void				deleteItem(unsigned int const id);
  void				addItem(AItem *item);

  AItem				*getItem(unsigned int const id) const;

  virtual bool			serialization(Trame &trame) const;
  static Inventory		*deserialization(Trame const &trame);
};

#endif

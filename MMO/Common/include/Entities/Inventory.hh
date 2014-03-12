//
// Inventory.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:15:58 2014 laurent ansel
// Last update Tue Mar 11 13:29:47 2014 alexis mestag
//

#ifndef 			__INVENTORY_HH__
# define 			__INVENTORY_HH__

# include			<list>
# include			"Utility/ISerialization.hh"
# include			"Entities/AItem.hh"
# include			"Database/Persistent.hh"
# include			"JsonFile/JsonFile.hh"
# include			"Utility/Wrapper.hpp"

class				Inventory : public ISerialization, public Persistent,
					    public ContainerWrapper<std::list<std::pair<AItem *,
											unsigned int>>>
{
private:
  std::string			_path;
  unsigned int			_money;
  unsigned int			_limit;

  void				loadInventory();

public:
  Inventory(std::string const &path = "");
  Inventory(Inventory const &rhs);
  virtual ~Inventory();

  Inventory			&operator=(Inventory const &rhs);

  void				serializationInventory() const;

  std::string const		&getPath() const;
  void				setPath(std::string const &path);

  container_type const		&getInventory() const;
  void				setInventory(container_type *inventory);

  unsigned int			getMoney() const;
  void				setMoney(unsigned int const money);
  void				addMoney(int const money);

  unsigned int			getLimit() const;
  void				setLimit(unsigned int const limit);

  void				deleteItem(unsigned int const id);
  void				addItem(AItem *item);
  void				addItem(AItem *item, unsigned int const nb);

  AItem				*getItem(unsigned int const id) const;
  AItem				*getAndDeleteItem(unsigned int const id);

  unsigned int			getIdItem(std::string const &name) const;

  virtual bool			serialization(Trame &trame) const;
  static Inventory		*deserialization(Trame const &trame);
};

#endif

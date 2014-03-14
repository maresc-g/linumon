//
// Inventory.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:15:58 2014 laurent ansel
// Last update Fri Mar 14 15:30:35 2014 laurent ansel
//

#ifndef 			__INVENTORY_HH__
# define 			__INVENTORY_HH__

# include			<list>
# include			"Utility/ISerialization.hh"
# include			"Entities/AItem.hh"
# include			"Database/Persistent.hh"
# include			"JsonFile/JsonFile.hh"
# include			"Utility/Wrapper.hpp"

template<typename T>
class				Stack;

class				Inventory : public ISerialization, public Persistent,
					    public ContainerWrapper<std::list<Stack<AItem> *> >
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

  void				deleteItem(unsigned int const stack);
  void				deleteItem(Stack<AItem> *stack);

  void				addItem(AItem *item);
  void				addItem(Stack<AItem> *stack);
  void				addItem(AItem *item, unsigned int const nb, bool const merge = true);

  AItem				*getItem(unsigned int const stack) const;
  AItem				*getAndDeleteItem(unsigned int const stack);

  unsigned int			getIdItem(std::string const &name) const;

  Stack<AItem>			*getStack(unsigned int const id) const;

  void				mergeStack(unsigned int const idStack, unsigned int const idStack2);
  unsigned int			splitStack(unsigned int const idStack, unsigned int const nb);

  virtual bool			serialization(Trame &trame) const;
  static Inventory		*deserialization(Trame const &trame);
};

# include			"Entities/Stack.hh"

#endif

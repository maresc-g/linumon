//
// Inventory.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:16:04 2014 laurent ansel
// Last update Fri Feb  7 13:08:26 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Inventory.hh"

Inventory::Inventory():
  _money(0),
  _limit(0)
{

}

Inventory::Inventory(Inventory const &rhs)
{
  *this = rhs;
}

Inventory::~Inventory()
{
}

Inventory			&Inventory::operator=(Inventory const &rhs)
{
  if (this != &rhs)
    {
      this->_money = rhs.getMoney();
      this->_limit = rhs.getLimit();
    }
  return (*this);
}

std::list<AItem *> const	&Inventory::getInventory() const
{
  return (_inventory);
}

void				Inventory::setInventory(std::list<AItem *> const &inventory)
{
  _inventory = inventory;
}

unsigned int			Inventory::getMoney() const
{
  return (_money);
}

void				Inventory::setMoney(unsigned int const money)
{
  _money = money;
}

unsigned int			Inventory::getLimit() const
{
  return (_limit);
}

void				Inventory::setLimit(unsigned int const limit)
{
  _limit = limit;
}

bool				Inventory::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["INVENTORY"]["MONEY"] = this->getMoney();
  trame["INVENTORY"]["LIMIT"] = this->getLimit();
  trame["INVENTORY"]["ITEMS"];
  for (auto it = _inventory.begin() ; it != _inventory.end() ; ++it)
    {
      str << "ITEM" << nb;
      ret = (*it)->serialization(trame(trame["INVENTORY"]["ITEMS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Inventory			*Inventory::deserializtion(Trame const &trame)
{
  Inventory			*inventory = NULL;
  std::list<AItem *>		*items = NULL;
  int				nb = 0;
  std::ostringstream		str;

  if (trame.isMember("INVENTORY"))
    {
      inventory = new Inventory;
      items = new std::list<AItem *>;
      inventory->setMoney(trame["INVENTORY"]["MONEY"].asUInt());
      inventory->setLimit(trame["INVENTORY"]["LIMIT"].asUInt());
      str << "ITEM" << nb;
      for (; !trame["INVENTORY"]["ITEMS"].isMember(str.str()) ; ++nb)
	{
	  items->push_back(AItem::deserialization(trame(trame["EQUIPMENT"]["ITEMS"][str.str()])));
	  str.str("");
	  str << "ITEM" << nb + 1;
	}
      inventory->setInventory(*items);
    }
  return (inventory);
}


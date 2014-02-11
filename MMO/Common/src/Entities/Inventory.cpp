//
// Inventory.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:16:04 2014 laurent ansel
// Last update Tue Feb 11 15:47:19 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Inventory.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"

Inventory::Inventory():
  Persistent(),
  _money(0),
  _limit(0),
  _inventory(new std::list<AItem *>)
{

}

Inventory::Inventory(Inventory const &rhs) :
  Persistent(rhs),
  _inventory(new std::list<AItem *>)
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
      this->setPath(rhs.getPath());
    }
  return (*this);
}

std::string const		&Inventory::getPath() const
{
  return (this->_path);
}

void				Inventory::setPath(std::string const &path)
{
  this->_path = path;
  this->loadInventory();
}

std::list<AItem *> const	&Inventory::getInventory() const
{
  return (*_inventory);
}

void				Inventory::setInventory(std::list<AItem *> *inventory)
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

void				Inventory::loadInventory()
{
  Trame				*file;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  if (JsonFile::readFile(*file, this->_path))
    {
      for (auto it = this->_inventory->begin() ; it != this->_inventory->end() ; ++it)
	delete *it;
      this->_inventory->clear();

      auto			members = file->getMemberNames();
      AItem			*toPush;

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  toPush = AItem::deserialization((*file)((*file)[*it]));
	  if (toPush)
	    this->_inventory->push_back(toPush);
	}
    }
}

void				Inventory::serializationInventory()
{
  Trame				*file;
  int				nb = 0;
  std::ostringstream		str;

  if (!this->_path.empty())
    {
      ObjectPoolManager::getInstance()->setObject(file, "trame");
      for (auto it = _inventory->begin() ; it != _inventory->end() ; ++it)
	{
	  str << "ITEM" << nb;
	  (*it)->serialization((*file)((*file)[str.str()]));
	  str.str("");
	  nb++;
	}
      file->writeInFile(this->_path);
    }
}

bool				Inventory::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["INVENTORY"]["MONEY"] = this->getMoney();
  trame["INVENTORY"]["LIMIT"] = this->getLimit();
  trame["INVENTORY"]["ITEMS"];
  for (auto it = _inventory->begin() ; it != _inventory->end() ; ++it)
    {
      str << "ITEM" << nb;
      ret = (*it)->serialization(trame(trame["INVENTORY"]["ITEMS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Inventory			*Inventory::deserialization(Trame const &trame)
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
      inventory->setInventory(items);
    }
  return (inventory);
}


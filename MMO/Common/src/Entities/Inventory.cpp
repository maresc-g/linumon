//
// Inventory.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:16:04 2014 laurent ansel
// Last update Fri Feb 28 13:30:27 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Inventory.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"

Inventory::Inventory():
  Persistent(),
  _money(0),
  _limit(0),
  _inventory(new std::list<std::pair<AItem *, unsigned int> >)
{

}

Inventory::Inventory(Inventory const &rhs) :
  Persistent(rhs),
  _inventory(new std::list<std::pair<AItem *, unsigned int> >)
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

std::list<std::pair<AItem *, unsigned int> > const	&Inventory::getInventory() const
{
  return (*_inventory);
}

void				Inventory::setInventory(std::list<std::pair<AItem *, unsigned int> > *inventory)
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

void				Inventory::addMoney(int const money)
{
  _money += money;
}

unsigned int			Inventory::getLimit() const
{
  return (_limit);
}

void				Inventory::setLimit(unsigned int const limit)
{
  _limit = limit;
}

void				Inventory::deleteItem(unsigned int const id)
{
  auto				it = this->_inventory->begin();

  for ( ; it != this->_inventory->end() && it->first->getId() != id ; ++it);
  if (it != this->_inventory->end() && it->first->getId() == id)
    {
      if (it->second == 1)
	{
	  this->_inventory->erase(it);
	  delete it->first;
	}
      else
	it->second--;
    }
}

void				Inventory::addItem(AItem *item)
{
  bool				set = false;

  for (auto it = this->_inventory->begin() ; !set && it != this->_inventory->end() ; ++it)
    {
      if (it->first->getName() == item->getName())
	{
	  if (it->second < 99)
	    {
	      it->second++;
	      delete item;
	    }
	  else
	    this->_inventory->push_back(std::make_pair(item, 1));
	  set = true;
	}
    }
  if (!set)
    this->_inventory->push_back(std::make_pair(item, 1));
}

AItem				*Inventory::getItem(unsigned int const id) const
{
  auto				it = this->_inventory->begin();

  for ( ; it != this->_inventory->end() && it->first->getId() != id ; ++it);
  if (it != this->_inventory->end() && it->first->getId() == id)
    return (it->first);
  return (NULL);
}

AItem				*Inventory::getAndDeleteItem(unsigned int const id) const
{
  auto				it = this->_inventory->begin();
  AItem				*item;

  for ( ; it != this->_inventory->end() && it->first->getId() != id ; ++it);
  if (it != this->_inventory->end() && it->first->getId() == id)
    {
      if (it->second == 1)
	{
	  this->_inventory->erase(it);
	  return (it->first);
	}
      else
	{
	  it->second--;
	  item = AItem::createCopy(it->first);
	  return (item);
	}
    }
  return (NULL);
}

unsigned int			Inventory::getIdItem(std::string const &name) const
{
  auto				it = this->_inventory->begin();

  for ( ; it != this->_inventory->end() && it->first->getName() != name ; ++it);
  if (it != this->_inventory->end() && it->first->getName() == name)
    return (it->first->getId());
  return (0);
}

void				Inventory::loadInventory()
{
  Trame				*file;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  if (JsonFile::readFile(*file, this->_path))
    {
      for (auto it = this->_inventory->begin() ; it != this->_inventory->end() ; ++it)
	delete it->first;
      this->_inventory->clear();

      auto			members = file->getMemberNames();
      AItem			*toPush;

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  toPush = AItem::deserialization((*file)((*file)[*it]), false);
	  if (toPush)
	    this->addItem(toPush);
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
	  for (unsigned int i = 0 ; i < it->second ; ++i)
	    {
	      str << nb;
	      it->first->serialization((*file)((*file)[str.str()]));
	      str.str("");
	      nb++;
	    }
	}
      file->writeInFile(this->_path);
    }
}

bool				Inventory::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["INV"]["MO"] = this->getMoney();
  trame["INV"]["LI"] = this->getLimit();
  trame["INV"]["ITS"];
  for (auto it = _inventory->begin() ; it != _inventory->end() ; ++it)
    {
      str << nb;
      ret = it->first->serialization(trame(trame["INV"]["ITS"][str.str()]));
      trame["INV"]["ITS"][str.str()]["NB"] = it->second;
      str.str("");
      nb++;
    }
  return (ret);
}

Inventory			*Inventory::deserialization(Trame const &trame)
{
  Inventory			*inventory = NULL;
  std::list<std::pair<AItem *, unsigned int> >	*items = NULL;

  if (trame.isMember("INV"))
    {
      inventory = new Inventory;
      items = new std::list<std::pair<AItem *, unsigned int> >;
      inventory->setMoney(trame["INV"]["MO"].asUInt());
      inventory->setLimit(trame["INV"]["LI"].asUInt());
      inventory->setInventory(items);
      if (trame["INV"].isMember("ITS"))
	{
	  auto			members = trame["INV"]["ITS"].getMemberNames();

	  for (auto it = members.begin() ; it != members.end() ; ++it)
	    {
	      for (unsigned int i = 0 ; i < trame["INV"]["ITS"][*it]["NB"].asUInt() ; ++i)
		{
		  std::cout << "IN FOR INVENTORY" << std::endl;
		  inventory->addItem(AItem::deserialization(trame(trame["INV"]["ITS"][*it])));
		  std::cout << "INVENTORY SIZE AFTER ADD " << inventory->getInventory().size() << std::endl;
		}
	    }
	    //	    items->push_back(AItem::deserialization(trame(trame["EQUIPMENT"]["ITEMS"][*it])));
	}
    }
  return (inventory);
}


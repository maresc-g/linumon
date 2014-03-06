//
// Inventory.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:16:04 2014 laurent ansel
// Last update Thu Mar  6 13:35:23 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Inventory.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"Loader/LoaderManager.hh"

Inventory::Inventory():
  Persistent(),
  ContainerWrapper<container_type>(),
  _money(0),
  _limit(0)
{

}

Inventory::Inventory(Inventory const &rhs) :
  Persistent(rhs), ContainerWrapper<container_type>()
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
      this->setMoney(rhs.getMoney());
      this->setLimit(rhs.getLimit());
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

Inventory::container_type const	&Inventory::getInventory() const
{
  return (this->getContainer());
}

void				Inventory::setInventory(container_type *inventory)
{
  this->setContainer(*inventory);
  delete inventory;
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
  auto				it = this->begin();

  for ( ; it != this->end() && it->first->getId() != id ; ++it);
  if (it != this->end() && it->first->getId() == id)
    {
      if (it->second == 1)
	{
	  delete it->first;
	  this->getContainer().erase(it);
	}
      else
	it->second--;
    }
}

void				Inventory::addItem(AItem *item)
{
  bool				set = false;

  for (auto it = this->begin() ; !set && it != this->end() ; ++it)
    {
      if (it->first->getName() == item->getName())
	{
	  if (it->second < 99)
	    {
	      it->second++;
	      delete item;
	    }
	  else
	    this->getContainer().push_back(std::make_pair(item, 1));
	  set = true;
	}
    }
  if (!set)
    this->getContainer().push_back(std::make_pair(item, 1));
}

void				Inventory::addItem(AItem *item, unsigned int const nb)
{
  bool				set = false;

  for (auto it = this->begin() ; !set && it != this->end() ; ++it)
    {
      if (it->first->getName() == item->getName())
	{
	  std::cout << "NB = " << nb << std::endl;
	  if (it->second + nb < 99)
	    {
	      it->second += nb;
	      delete item;
	    }
	  else
	    {
	      it->second += nb;
	      this->getContainer().push_back(std::make_pair(item, it->second - 99));
	      if (it->second > 99)
		it->second = 99;
	    }
	  set = true;
	}
    }
  if (!set)
    {
      unsigned int	i = nb;
      for (; i > 99 ; i -= 99)
	this->getContainer().push_back(std::make_pair(item, 99));
      this->getContainer().push_back(std::make_pair(item, i));
    }
}

AItem				*Inventory::getItem(unsigned int const id) const
{
  auto				it = this->begin();

  for ( ; it != this->end() && it->first->getId() != id ; ++it);
  if (it != this->end() && it->first->getId() == id)
    return (it->first);
  return (NULL);
}

AItem				*Inventory::getAndDeleteItem(unsigned int const id)
{
  auto				it = this->begin();
  AItem				*item;

  for ( ; it != this->end() && it->first->getId() != id ; ++it);
  if (it != this->end() && it->first->getId() == id)
    {
      if (it->second == 1)
	{
	  item = it->first;
	  this->getContainer().erase(it);
	  return (item);
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
  auto				it = this->begin();

  for ( ; it != this->end() && it->first->getName() != name ; ++it);
  if (it != this->end() && it->first->getName() == name)
    return (it->first->getId());
  return (0);
}

void				Inventory::loadInventory()
{
  Trame				*file;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  if (JsonFile::readFile(*file, this->_path))
    {
      for (auto it = this->begin() ; it != this->end() ; ++it)
	delete it->first;
      this->getContainer().clear();

      auto			members = file->getMemberNames();
      AItem			*item;

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  item = LoaderManager::getInstance()->getItemLoader(*it);
	  if (item)
	    this->addItem(item, (*file)[*it].asUInt());

	  // toPush = AItem::deserialization((*file)((*file)[*it]), false);
	  // if (toPush)
	  //   this->addItem(toPush, (*file)[*it]["NB"].asUInt());
	}
    }
}

void				Inventory::serializationInventory()
{
  Trame				*file;
  // int				nb = 0;
  // std::ostringstream		str;

  if (!this->_path.empty())
    {
      ObjectPoolManager::getInstance()->setObject(file, "trame");
      for (auto it = this->begin() ; it != this->end() ; ++it)
	{
	  // for (unsigned int i = 0 ; i < it->second ; ++i)
	  //   {
	  // str << nb;
	  if (file->isMember(it->first->getName()))
	    (*file)[it->first->getName()] = (*file)[it->first->getName()].asUInt() + it->second;
	  else
	    (*file)[it->first->getName()] = it->second;

	  // it->first->serialization((*file)((*file)[str.str()]));
	  // (*file)[str.str()]["NB"] = it->second;
	  // str.str("");
	  // nb++;
	    // }
	}
      file->writeInFile(this->_path);
    }
}

bool				Inventory::serialization(Trame &trame) const
{
  bool				ret = true;
  // int				nb = 0;
  // std::ostringstream		str;

  trame["INV"]["MO"] = this->getMoney();
  trame["INV"]["LI"] = this->getLimit();
  trame["INV"]["ITS"];
  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      // str << nb;
      //      ret = it->first->serialization(trame(trame["INV"]["ITS"][str.str()]));
      if (trame["INV"]["ITS"].isMember(it->first->getName()))
	trame["INV"]["ITS"][it->first->getName()] = trame["INV"]["ITS"][it->first->getName()].asUInt() + it->second;
      else
	trame["INV"]["ITS"][it->first->getName()] = it->second;
      // str.str("");
      // nb++;
    }
  return (ret);
}

Inventory			*Inventory::deserialization(Trame const &trame)
{
  Inventory			*inventory = NULL;
  AItem				*item;

  if (trame.isMember("INV"))
    {
      inventory = new Inventory;
      inventory->setMoney(trame["INV"]["MO"].asUInt());
      inventory->setLimit(trame["INV"]["LI"].asUInt());
      if (trame["INV"].isMember("ITS"))
	{
	  auto			members = trame["INV"]["ITS"].getMemberNames();

	  for (auto it = members.begin() ; it != members.end() ; ++it)
	    {
	      // for (unsigned int i = 0 ; i < trame["INV"]["ITS"][*it]/*["NB"]*/.asUInt() ; ++i)
	      // 	{
		  std::cout << "IN FOR INVENTORY" << std::endl;
		  item = LoaderManager::getInstance()->getItemLoader(*it);
		  if (item)
		    inventory->addItem(item, trame["INV"]["ITS"][*it].asUInt());
		  // item = (**LoaderManager::getInstance()->getStuffLoader())->getValue(*it);
		  // if (item)
		  //   inventory->addItem(item, trame["INV"]["ITS"][*it]/*["NB"]*/.asUInt());
		  // else
		  //   {
		  //     item = (**LoaderManager::getInstance()->getConsumableLoader())->getValue(*it);
		  //     if (item)
		  // 	inventory->addItem(item, trame["INV"]["ITS"][*it]/*["NB"]*/.asUInt());
		  //   }
		  std::cout << "INVENTORY SIZE AFTER ADD " << inventory->size() << std::endl;
		// }
	    }
	}
    }
  return (inventory);
}


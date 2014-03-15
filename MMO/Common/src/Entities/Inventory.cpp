//
// Inventory.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 11:16:04 2014 laurent ansel
// Last update Sat Mar 15 16:55:26 2014 laurent ansel
//

#include			<stdlib.h>
#include			<sstream>
#include			"Entities/Inventory.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"Loader/LoaderManager.hh"

Inventory::Inventory(std::string const &path):
  ContainerWrapper<container_type>(),
  _path(path),
  _money(0),
  _limit(0)
{

}

Inventory::Inventory(Inventory const &rhs) :
  ContainerWrapper<container_type>()
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

void				Inventory::deleteItem(unsigned int const stack)
{
  auto				it = this->begin();

  for ( ; it != this->end() && (*it)->getId() != stack ; ++it);
  if (it != this->end() && (*it)->getId() == stack)
    if ((*it)->getNb() > 0)
      *(*it) -= 1;
}

void				Inventory::deleteItem(Stack<AItem> *stack)
{
  auto				it = this->begin();
  unsigned int			supp = stack->getNb();
  bool				set = false;

  for ( ; it != this->end() && !set ; ++it)
    if (((*it)->getId() != 0 && (*it)->getId() == stack->getId()))
      {
	if (static_cast<int>((*it)->getNb() - supp) >= 0)
	  {
	    *(*it) -= supp;
	    supp = 0;
	    set = true;
	  }
	else
	  {
	    supp -= (*it)->getNb();
	    (*it)->setNb(0);
	  }
      }
  if (!set)
    for ( ; it != this->end() && !set ; ++it)
      if ((**it == stack->getItem()->getName()))
	{
	  if (static_cast<int>((*it)->getNb() - supp) >= 0)
	    {
	      *(*it) -= supp;
	      supp = 0;
	      set = true;
	    }
	  else
	    {
	      supp -= (*it)->getNb();
	      (*it)->setNb(0);
	    }
	}

}

void				Inventory::addItem(AItem *item)
{
  bool				set = false;
  Stack<AItem>			*tmp = NULL;

  for (auto it = this->begin() ; !set && it != this->end() ; ++it)
    {
      if (!tmp && (**it))
	tmp = *it;
      if (**it == item->getName())
	{
	  if ((*it)->getNb() < 99)
	    {
	      **it += 1;
	      set = true;
	    }
	}
    }
  if (!set && tmp)
    {
      tmp->setItem(item);
      tmp->setNb(1);
    }
  else if (!set)
    this->getContainer().push_back(new Stack<AItem>(this->getContainer().size(), item, 1));
}

void				Inventory::addItem(AItem *item, unsigned int const nb, bool const merge)
{
  bool				set = false;
  Stack<AItem>			*tmp = NULL;
  unsigned int			nbTmp = nb;

  for (auto it = this->begin() ; !set && it != this->end() ; ++it)
    {
      if (!tmp && (**it))
	tmp = *it;
      if (merge)
	{
	  if (**it == item->getName())
	    {
	      if (**it + nbTmp <= 99)
		{
		  **it += nbTmp;
		  set = true;
		}
	      else
		{
		  nbTmp = (**it + nbTmp - 99);
		  (*it)->setNb(99);
		}
	    }
	}
    }
  while (!set && nbTmp > 0)
    {
      if (!set && !tmp)
	{
	  tmp = new Stack<AItem>(this->getContainer().size(), item, 0);
	  this->getContainer().push_back(tmp);
	}
      if (!set && tmp)
	{
	  tmp->setItem(item);
	  if (nbTmp > 99)
	    {
	      tmp->setNb(99);
	      nbTmp -= 99;
	    }
	  else
	    {
	      tmp->setNb(nbTmp);
	      set = true;
	    }
	}
      for (auto it = this->begin() ; !set && it != this->end() ; ++it)
	if (!tmp && **it)
	  tmp = *it;
    }
}

void				Inventory::addItem(Stack<AItem> *stack)
{
  if (stack)
    this->addItem(stack->getItem(), stack->getNb());
}

AItem				*Inventory::getItem(unsigned int const stack) const
{
  auto				it = this->begin();

  for ( ; it != this->end() && (*it)->getId() != stack ; ++it);
  if (it != this->end() && (*it)->getId() == stack)
    return ((*it)->getItem());
  return (NULL);
}

AItem				*Inventory::getAndDeleteItem(unsigned int const stack)
{
  auto				it = this->begin();

  for ( ; it != this->end() && (*it)->getId() != stack ; ++it);
  if (it != this->end() && (*it)->getId() == stack)
    {
      if ((*it)->getNb() > 0)
	{
	  **it -= 1;
	  return ((*it)->getItem());
	}
    }
  return (NULL);
}

unsigned int			Inventory::getIdItem(std::string const &name) const
{
  auto				it = this->begin();

  for ( ; it != this->end() && **it != name ; ++it);
  if (it != this->end() && **it == name)
    return ((*it)->getItem()->getId());
  return (0);
}

Stack<AItem>			*Inventory::getStack(unsigned int const id) const
{
  for (auto it = this->begin() ; it != this->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

void				Inventory::mergeStack(unsigned int const idStack, unsigned int const idStack2)
{
  Stack<AItem>			*stack1 = getStack(idStack);
  Stack<AItem>			*stack2 = getStack(idStack2);

  std::cout << "MERGE => "<< idStack << " <=> " << idStack2 << std::endl;
  if (stack1 && stack2)
    {
      std::cout << "STACK (" << stack1->getNb() << ") <=> STACK2 (" << stack2->getNb() << ")" << std::endl;
      if (stack2->getNb() + stack1->getNb() <= 99)
	{
	  std::cout << "MERGE S1 ET S2" << std::endl;
	  *stack1 += stack2->getNb();
	  stack2->setNb(0);
	  stack2->setItem(NULL);
	  std::cout << "STACK (" << stack1->getNb() << ") <=> STACK2 (" << stack2->getNb() << ")" << std::endl;
	}
      else
	{
	  std::cout << "SEMIMERGE" << std::endl;
	  unsigned int		nb = stack2->getNb() + stack1->getNb() - 99;

	  stack1->setNb(99);
	  stack2->setNb(nb);
	}
    }
}

unsigned int			Inventory::splitStack(unsigned int const idStack, unsigned int const nb)
{
  Stack<AItem>			*stack = getStack(idStack);
  Stack<AItem>			*tmp = NULL;
  unsigned int			newStack = 0;

  if (stack && stack->getNb() >= nb)
    {
      for (auto it = this->begin() ; it != this->end() ; ++it)
	if (!tmp && **it)
	  {
	    tmp = *it;
	    break;
	  }
      if (!tmp)
	{
	  tmp = new Stack<AItem>(this->getContainer().size(), stack->getItem(), nb);
	  newStack = tmp->getId();
	  this->getContainer().push_back(tmp);
	  *stack -= nb;
	}
      else
	{
	  newStack = tmp->getId();
	  tmp->setNb(nb);
	  tmp->setItem(stack->getItem());
	  *stack -= nb;
	}
    }
  return (newStack);
}


void				Inventory::loadInventory()
{
  Trame				*file;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  if (JsonFile::readFile(*file, this->_path))
    {
      for (auto it = this->begin() ; it != this->end() ; ++it)
	delete (*it);
      this->getContainer().clear();

      auto			membersNb = file->getMemberNames();

      for (auto inb = membersNb.begin() ; inb != membersNb.end() ; ++inb)
      	{
      	  auto			members = (*file)[*inb].getMemberNames();
      	  AItem			*item;

	  //		  this->getContainer().push_back(new Stack(atol((*inb).c_str())));
      	  for (auto it = members.begin() ; it != members.end() ; ++it)
      	    {
      	      item = LoaderManager::getInstance()->getItemLoader(*it);
      	      if (item)
		this->addItem(item, (*file)[*inb][*it].asUInt(), false);
      	    }
      	}
    }
}

void				Inventory::serializationInventory() const
{
  Trame				*file;
  std::ostringstream		str;

  if (!this->_path.empty())
    {
      ObjectPoolManager::getInstance()->setObject(file, "trame");
      for (auto it = this->begin() ; it != this->end() ; ++it)
	{
	  // str << (*it)->getId();
	  // (*file)[str.str()][(*it)->getItem()->getName()] = (*it)->getNb();
	  // str.str("");
	  (*it)->serialization(*file);
	}
      file->writeInFile(this->_path);
    }
}

bool				Inventory::serialization(Trame &trame) const
{
  bool				ret = true;
  // std::ostringstream		str;

  trame["INV"]["MO"] = this->getMoney();
  trame["INV"]["LI"] = this->getLimit();
  trame["INV"]["ITS"];
  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      //      str << (*it)->getId();
      // if (trame["INV"]["ITS"].isMember((*it)->getId()->getName()))
      // 	trame["INV"]["ITS"][(*it)->getId()->getName()] = trame["INV"]["ITS"][(*it)->getId()->getName()].asUInt() + (*it);
      // else
      // 	trame["INV"]["ITS"][(*it)->getId()->getName()] = (*it);
      //      trame["INV"]["ITS"][str.str()][(*it)->getItem()->getName()] = (*it)->getNb();

    // if ((*it)->getItem())
    //   {
	//	str << (*it)->getId();
	(*it)->serialization(trame(trame["INV"]["ITS"]));
	//str.str("");
      // }
    }
  return (ret);
}

Inventory			*Inventory::deserialization(Trame const &trame)
{
  Inventory			*inventory = NULL;
  // AItem				*item;
  Stack<AItem>			*tmp = NULL;

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
	      // auto		membersItem = trame["INV"]["ITS"][*it].getMemberNames();

	      // for (auto itItem = membersItem.begin() ; itItem != membersItem.end() ; ++itItem)
	      // 	{
	      std::cout << "IN FOR INVENTORY" << std::endl;
	      tmp = Stack<AItem>::deserialization(trame(trame["INV"]["ITS"][*it]));
	      if (tmp)
		{
		  tmp->setId(atol((*it).c_str()));
		  inventory->getContainer().push_back(tmp);
		}

	      //		  inventory->getContainer().push_back(new Stack(atol((*it).c_str())));
	      // item = LoaderManager::getInstance()->getItemLoader(*itItem);
	      // if (item)
	      //   inventory->addItem(item, trame["INV"]["ITS"][*it][*itItem].asUInt());
	      std::cout << "INVENTORY SIZE AFTER ADD " << inventory->size() << std::endl;
	      //	    }
	    }
	}
    }
  return (inventory);
}


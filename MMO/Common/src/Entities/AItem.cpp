//
// AItem.cpp for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:18:02 2013 alexis mestag
// Last update Thu Feb  6 16:10:15 2014 laurent ansel
//

#include			"Entities/AItem.hh"

AItem::AItem() :
  AEntity("", eEntity::ITEM),
  _itemType(eItem::NONE)
{

}

AItem::AItem(std::string const &name, AItem::eItem const type) :
  AEntity(name, eEntity::ITEM),
  _itemType(type)
{

}

AItem::AItem(AItem const &rhs) :
  AEntity(rhs)
{
  *this = rhs;
}

AItem::~AItem()
{

}

AItem				&AItem::operator=(AItem const &rhs)
{
  if (this != &rhs)
    {
      this->_itemType = rhs.getItemType();
    }
  return (*this);
}

AItem::eItem			AItem::getItemType() const
{
  return (this->_itemType);
}

void				AItem::setItemType(AItem::eItem const item)
{
  this->_itemType = item;
}

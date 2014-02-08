//
// AItem.cpp for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:18:02 2013 alexis mestag
// Last update Sat Feb  8 16:29:56 2014 laurent ansel
//

#include			"Entities/AItem.hh"
#include			"Entities/Stuff.hh"

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

bool				AItem::serialization(Trame &trame) const
{
  trame["TYPE"] = this->_itemType;
  return (true);
}

AItem				*AItem::deserialization(Trame const &trame)
{
  AItem				*item = NULL;

  if (trame["TYPE"].asInt() == eItem::STUFF)
    item = reinterpret_cast<Stuff *>(Stuff::deserialization(trame));
  if (item)
    item->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
  return (item);
}

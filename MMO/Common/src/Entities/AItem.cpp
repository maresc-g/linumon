//
// AItem.cpp for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:18:02 2013 alexis mestag
// Last update Thu Feb 20 13:36:12 2014 laurent ansel
//

#include			"Entities/AItem.hh"
#include			"Entities/Stuff.hh"
#include			"Entities/Consumable.hh"
#include			"Entities/Ressource.hh"

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

AItem				*AItem::deserialization(Trame const &trame)
{
  AItem				*item = NULL;

  if (!(item = reinterpret_cast<Stuff *>(Stuff::deserialization(trame))))
    if (!(item = reinterpret_cast<Consumable *>(Consumable::deserialization(trame))))
      item = reinterpret_cast<Ressource *>(Ressource::deserialization(trame));
  return (item);
}

AItem				*AItem::createCopy(AItem *rhs)
{
  AItem				*item = NULL;

  if (rhs->getItemType() == AItem::STUFF)
    item = new Stuff(static_cast<Stuff const &>(*rhs));
  else if (rhs->getItemType() == AItem::CONSUMABLE)
    item = new Consumable(static_cast<Consumable const &>(*rhs));
  else
    item = new Ressource(static_cast<Ressource const &>(*rhs));
  if (item)
    item->setId(rhs->getId());
  return (item);
}

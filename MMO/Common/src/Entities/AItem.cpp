//
// AItem.cpp for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:18:02 2013 alexis mestag
// Last update Thu Nov 28 21:36:09 2013 alexis mestag
//

#include			"Entities/AItem.hh"

AItem::AItem() :
  AEntity("", eEntity::ITEM)
{

}

AItem::AItem(std::string const &name) :
  AEntity(name, eEntity::ITEM)
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

    }
  return (*this);
}

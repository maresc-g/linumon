//
// InventoryManager.hh<2> for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:33:41 2014 laurent ansel
// Last update Thu Mar 13 15:57:04 2014 laurent ansel
//

#ifndef 			__INVENTORYMANAGER_HH__
# define 			__INVENTORYMANAGER_HH__

#include			"Trame/Trame.hh"

class				InventoryManager
{
private:
  bool				useObject(Trame *trame);
  bool				merge(Trame *trame);
  bool				newStack(Trame *trame);

public:
  InventoryManager();
  virtual ~InventoryManager();
};

#endif

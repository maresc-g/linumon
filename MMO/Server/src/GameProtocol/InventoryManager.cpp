//
// InventoryManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:31:31 2014 laurent ansel
// Last update Tue Feb 11 14:30:28 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/InventoryManager.hh"
#include			"Server/Server.hh"

InventoryManager::InventoryManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&InventoryManager::useObject), this);
  Server::getInstance()->addFuncProtocol("USEOBJECT", func);

  func = std::bind1st(std::mem_fun(&InventoryManager::deleteObject), this);
  Server::getInstance()->addFuncProtocol("DELETEOBJECT", func);
}

InventoryManager::~InventoryManager()
{

}

bool				InventoryManager::useObject(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("USEOBJECT"))
    {
      
      return (true);
    }
  return (false);
}

bool				InventoryManager::deleteObject(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("DELETEOBJECT"))
    {
      return (true);
    }
  return (false);
}

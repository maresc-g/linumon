//
// InventoryManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:31:31 2014 laurent ansel
// Last update Wed Mar 12 16:22:06 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/InventoryManager.hh"
#include			"Server/Server.hh"

InventoryManager::InventoryManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&InventoryManager::useObject), this);
  Server::getInstance()->addFuncProtocol("USEOBJECT", func);

  func = std::bind1st(std::mem_fun(&InventoryManager::merge), this);
  Server::getInstance()->addFuncProtocol("MERGE", func);

  func = std::bind1st(std::mem_fun(&InventoryManager::newStack), this);
  Server::getInstance()->addFuncProtocol("NEWSTACK", func);
}

InventoryManager::~InventoryManager()
{

}

bool				InventoryManager::useObject(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("USEOBJECT"))
    {
      ClientManager::getInstance()->playerObject((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["USEOBJECT"]["TARGET"].asUInt(), (*trame)[CONTENT]["USEOBJECT"]["IDSTACK"].asUInt());
      return (true);
    }
  return (false);
}

bool				InventoryManager::merge(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("MERGE"))
    {
      ClientManager::getInstance()->merge((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["MERGE"]["IDSTACK"].asUInt(), (*trame)[CONTENT]["MERGE"]["IDSTACK2"].asUInt());
      return (true);
    }
  return (false);
}

bool				InventoryManager::newStack(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("NEWSTACK"))
    {
      ClientManager::getInstance()->newStack((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["NEWSTACK"]["IDSTACK"].asUInt(), (*trame)[CONTENT]["NEWSTACK"]["NB"].asUInt());
      return (true);
    }
  return (false);
}

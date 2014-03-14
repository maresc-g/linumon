//
// Interaction.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:34:41 2014 laurent ansel
// Last update Fri Mar 14 17:11:48 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/Interaction.hh"
#include			"Server/Server.hh"
#include			"Battle/BattleManager.hh"

Interaction::Interaction()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&Interaction::interaction), this);
  Server::getInstance()->addFuncProtocol("INTERACTION", func);
}

Interaction::~Interaction()
{

}

bool				Interaction::interaction(Trame *trame)
{
  bool				ret = false;
  static std::map<Interaction::eInteraction, std::function<bool (Trame *)> > map =
    {
      {Interaction::eInteraction::AGRO,		std::bind1st(std::mem_fun(&Interaction::agro), this)},
      {Interaction::eInteraction::TRADE,	std::bind1st(std::mem_fun(&Interaction::trade), this)}
    };
  eInteraction			type;

  if ((*trame)[CONTENT].isMember("INTERACTION"))
    {
      type = static_cast<Interaction::eInteraction>((*trame)[CONTENT]["INTERACTION"]["TYPE"].asInt());
      ret = map[type](trame);
    }
  return (ret);
}


bool				Interaction::agro(Trame *trame)
{
  bool				ret = false;
  std::string			target = (*trame)[CONTENT]["INTERACTION"]["NAME"].asString();
  Player			*player2;
  Player			*player1;
  unsigned int			id2;
  unsigned int			id = (*trame)[HEADER]["IDCLIENT"].asUInt();
  Repository<Player>		*rp = &Database::getRepository<Player>();

  player2 = rp->getByName(target);
  if (player2)
    {
      id2 = player2->getUser().getId();
      ClientManager::getInstance()->startBattle(id, player1);
      ClientManager::getInstance()->startBattle(id2, player2);
      BattleManager::getInstance()->newBattle(player1, player2);
      ret = true;
    }
  return (ret);
}

bool				Interaction::trade(Trame *trame)
{
  bool				ret = false;
  std::string			target = (*trame)[CONTENT]["INTERACTION"]["NAME"].asString();
  Player			*player2;
  Player			*player1;
  unsigned int			id2;
  unsigned int			id = (*trame)[HEADER]["IDCLIENT"].asUInt();
  Repository<Player>		*rp = &Database::getRepository<Player>();

  player2 = rp->getByName(target);
  if (player2)
    {
      id2 = player2->getUser().getId();
      ClientManager::getInstance()->startTrade(id, player1);
      ClientManager::getInstance()->startTrade(id2, player2);
      TradeManager::getInstance()->newTrade(player1, player2);
      ret = true;
    }
  return (ret);
}

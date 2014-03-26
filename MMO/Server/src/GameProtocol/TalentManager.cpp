//
// TalentManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:23:10 2014 laurent ansel
// Last update Tue Mar 25 21:49:34 2014 alexis mestag
//

#include			<functional>
#include			"GameProtocol/TalentManager.hh"
#include			"Server/Server.hh"

TalentManager::TalentManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&TalentManager::talents), this);
  Server::getInstance()->addFuncProtocol("TALENTS", func);
}

TalentManager::~TalentManager()
{

}

bool				TalentManager::talents(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("TALENTS"))
    {
      auto			members = (*trame)["TALENTS"].getMemberNames();

      /*
      ** Possible fail beceause there's Player::Talents::_currentPoins serialized too
      */
      for (auto it = members.begin() ; it != members.end() ; ++it)
	ClientManager::getInstance()->setPlayerTalent((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)["TALENTS"][*it]["NAME"].asString(), (*trame)["TALENTS"][*it]["PTS"].asUInt());
      return (true);
    }
  return (false);
}

//
// TalentManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:23:10 2014 laurent ansel
// Last update Wed Mar 26 10:52:44 2014 guillaume marescaux
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
      auto			members = (*trame)[CONTENT]["TALENTS"].getMemberNames();

      /*
      ** Possible fail beceause there's Player::Talents::_currentPoins serialized too
      */
      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  if ((*it) != "PTS")
	    ClientManager::getInstance()->setPlayerTalent((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["TALENTS"][*it]["NAME"].asString(), (*trame)[CONTENT]["TALENTS"][*it]["PTS"].asUInt());
	}
      return (true);
    }
  return (false);
}

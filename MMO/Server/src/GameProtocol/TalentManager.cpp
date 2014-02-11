//
// TalentManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:23:10 2014 laurent ansel
// Last update Mon Feb 10 15:17:15 2014 laurent ansel
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
      ClientManager::getInstance()->setPlayerTalents(trame);
      return (true);
    }
  return (false);
}

/*
** DON4T FORGET ABOUT TALENT EFFECT
**
*/

void				TalentManager::updateTalents(Trame *trame, Player *player)
{
  bool				set = false;

  if (player)
    {
      Repository<Talent>	*rp = &Database::getRepository<Talent>();
      auto			members = (*trame)["TALENTS"].getMemberNames();
      std::list<Talent *>	talent = player->getTalents();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  for (auto search = talent.begin() ; search != talent.end() && !set ; ++search)
	    if ((*search)->getModel().getName() == *it)
	      {
		if ((*search)->getCurrentPoints() != (*trame)["TALENTS"][*it]["CURRENTPTS"].asInt())
		  {
		    (*search)->setCurrentPoints((*trame)["TALENTS"][*it]["CURRENTPTS"].asInt());
		    rp->update(**search);
		  }
		set = true;
	      }
	  if (!set)
	    {
	      Talent		*newTalent = Talent::deserialization((*trame)((*trame)["TALENTS"][*it]));

	      if (newTalent)
		{
		  player->addTalent(newTalent);
		  rp->persist(*newTalent);
		}
	    }
	  set = false;
	}
    }
}

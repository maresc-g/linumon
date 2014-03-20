//
// Battle.cpp for Battle in /home/maitre_c/work/linumon/MMO/Common/src/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 15:37:55 2014 antoine maitre
// Last update Thu Mar 20 16:36:41 2014 alexis mestag
//

#include				"Battle/Battle.hh"
#include				"Database/Repositories/StatKeyRepository.hpp"

Battle::Battle(unsigned int const id, eBattle const type, unsigned int const mobNumber, Player *player1, Player *player2)
  : _id(id), _type(type),
    _mobNumber(mobNumber), _money(0), _exp(0), _success(true)
{
  // static StatKey const			*hpKey = Database::getRepository<StatKey>().getByName("HP");
  unsigned int i = 0;

  for (auto it = player1->getDigitaliser().getBattleMobs().begin(); it != player1->getDigitaliser().getBattleMobs().end(); it++)
    (*it)->enterBattle();
  for (auto it = player2->getDigitaliser().getBattleMobs().begin(); it != player2->getDigitaliser().getBattleMobs().end(); it++)
    (*it)->enterBattle();
  for (auto it = player1->getDigitaliser().getBattleMobs().begin(); it != player1->getDigitaliser().getBattleMobs().end() && i++ < mobNumber; it++)
    this->_mobs.push_back((*it));
  i = 0;
  for (auto it = player2->getDigitaliser().getBattleMobs().begin(); it != player2->getDigitaliser().getBattleMobs().end() && i++ < mobNumber; it++)
    this->_mobs.push_back((*it));
  if (player1->getType() == Player::PlayerType::PLAYER)
    this->trameLaunchBattle(player1->getUser().getId(), player2);
  if (player2->getType() == Player::PlayerType::PLAYER)
    this->trameLaunchBattle(player2->getUser().getId(), player1);
  this->_players.push_back(player1);
  this->_players.push_back(player2);
  this->_mobs.sort(compareSpeed);
  this->replace();
  this->next();
}

Battle::~Battle()
{
  if (this->_success)
    {
      this->trameEndBattle();
      for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	if ((*it)->getType() == Player::PlayerType::PLAYER)
	  ClientManager::getInstance()->endBattle((*it)->getId());
    }
}

void					Battle::disconnect(unsigned int const idPlayer) const
{
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    if ((*it)->getId() != idPlayer && (*it)->getType() == Player::PlayerType::PLAYER)
      Server::getInstance()->newClientStateInStandBy((*it)->getUser().getId(), Client::eState::GAME);
}

unsigned int				Battle::getID() const
{
  return (this->_id);
}

Battle::eBattle 			Battle::getType() const
{
  return (this->_type);
}

bool					Battle::checkEnd()
{
  unsigned int				i;

  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    {
      i = 0;
      for (auto itb = this->_mobs.begin(); itb != this->_mobs.end(); itb++)
	{
	  if ((*it)->isMyMob((*itb)->getId()) && (*itb)->getCurrentStat("HP") <= 0)
	    i++;
	  if (i == _mobNumber)
	    {
	      this->_idLooser = (*it)->getId();
	      return (true);
	    }
	  if ((*it)->getType() == Player::PlayerType::AI)
	    std::cout << "LA TAILLE DE LA LISTE DE MOB EST DE " << static_cast<AI *>((*it))->getSizeList() << std::endl;;
	  if ((*it)->getType() == Player::PlayerType::AI && static_cast<AI *>((*it))->getSizeList() == 0)
	    {
	      std::cout << "THIS IS THE END OF THIS BATTLE!!!!" << std::endl;
	      this->_idLooser = (*it)->getId();
	      return (true);
	    }
	}
    }
  return (false);
  
}

bool					Battle::spell(unsigned int const launcher, unsigned int const target, Spell *spell) //, int id_lanceur
{
  static StatKey const			*hpKey = Database::getRepository<StatKey>().getByName("HP");
  Mob					*mobLauncher = NULL;
  Mob					*mobTarget = NULL;
  int					hpChange = 0;

  for (auto it = this->_mobs.begin(); it != this->_mobs.end(); it++)
    {
      if ((*it)->getId() == launcher)
	mobLauncher = (*it);
      if ((*it)->getId() == target)
	mobTarget = (*it);
    }
  if (mobLauncher && mobTarget)
    {
      hpChange = mobTarget->getCurrentStat("HP");
      (*spell)(*mobLauncher, *mobTarget);
      for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	if ((*it)->getType() == Player::PlayerType::PLAYER)
	  {
	    hpChange = mobTarget->getCurrentStat("HP") - hpChange;
	    this->trameSpell((*it)->getUser().getId(), spell, launcher, target);
	    this->trameSpellEffect((*it)->getUser().getId(), target, hpChange);
	  } 
      Stats const			&statMob = mobTarget->getCurrentStats();
      if (statMob.getStat(*hpKey) <= 0)
	{
	  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	    if ((*it)->getType() == Player::PlayerType::PLAYER)
	      this->trameDeadMob((*it)->getUser().getId(), target);
	  this->replace();
	}
    }
  else
    std::cout << "Je ne trouve pas les protagoniste" << std::endl;
  return (this->checkEnd());
}

bool					Battle::dswitch(unsigned int const target, unsigned int const newmob)
{
  Player				*tmp = NULL;
  for (auto itMob = this->_mobs.begin(); itMob != this->_mobs.end(); itMob++)
    if ((*itMob)->getId() == target)
      for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	if ((*it)->isMyMob((*itMob)->getId()))
	  {
	    tmp = (*it);
	    (*itMob) = (Mob *)(&(*it)->getMob(newmob));
	  }
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    {
      if ((*it)->getType() == Player::PlayerType::PLAYER)
	this->trameSwitch((*it)->getUser().getId(), target, newmob, tmp->getId());
      else
	static_cast<AI *>((*it))->dswitch(target, newmob);
    }
  this->replace();
  return (this->checkEnd());
}

bool					Battle::capture(unsigned int const target)
{
  if (this->_type == PVP)
    return (false);
  else
    for (auto it = this->_mobs.begin(); it != this->_mobs.end(); it++)
      {
	if ((*it)->getId() == target)
	  {
	    if (this->_players.front()->capture(*(*it)))
	      {
		static_cast<AI *>(this->_players.back())->remove(target);
		this->_mobs.erase(it);
		this->trameCapture(this->_players.front()->getUser().getId(), target, true);
	      }
	    else
	      this->trameCapture(this->_players.front()->getUser().getId(), target, false);
	    break;
	  }
      }
  return (this->checkEnd());
}

void					Battle::replace()
{
  for (auto it = this->_mobs.begin(); it != this->_mobs.end(); it++)
    {
      std::cout << "ONE" << std::endl;
      if ((*it)->getCurrentStat("HP") == 0)
	{
	  std::cout << "TWO" << std::endl;
	  for (auto itb = this->_players.begin(); itb != this->_players.end(); itb++)
	    {
	      std::cout << "THREE" << std::endl;
	      if ((*itb)->isMyMob((*it)->getId()))
		{
		  std::cout << "FOUR" << std::endl;
		  for (auto itc = (*itb)->getDigitaliser().getBattleMobs().begin(); itc != (*itb)->getDigitaliser().getBattleMobs().end(); itc++)
		    {
		      std::cout << "REPLACE EN ACTION" << std::endl;
		      auto tmp = std::find(this->_mobs.begin(), this->_mobs.end(), (*itc));
		      if ((*itc)->getCurrentStat("HP") > 0 && tmp == this->_mobs.end())
			{
			  dswitch((*it)->getId(), (*itc)->getId());
			  std::cout << "SA DEVRAIT MARCHER" << std::endl;
			  break;
			}
		    }
		}
	    }
	}
    }
}

void					Battle::next()
{
  auto tmp = this->_mobs.front();
  this->_mobs.pop_front();
  this->_mobs.push_back(tmp);
  if (tmp->getCurrentStat("HP") <= 0 && !this->checkEnd())
    {
      this->next();
      return;
    }
  else if (this->checkEnd())
    return;
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    if ((*it)->getType() == Player::PlayerType::PLAYER)
      this->trameTurnTo((*it)->getUser().getId(), tmp->getId());
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    {
      if ((*it)->isMyMob(tmp->getId()) && (*it)->getType() == Player::PlayerType::AI)
	{
	  auto tmp2 = static_cast<AI *>((*it))->action(tmp->getId(), this->_mobNumber);
	  if (!this->spell(std::get<0>(tmp2), std::get<1>(tmp2), (Spell *)std::get<2>(tmp2)))
	    this->next();
	  return;
	}
    }
}

bool					Battle::isInThisBattle(unsigned int const idPlayer)
{
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    if ((*it)->getId() == idPlayer)
      {
	// this->_money = 0;
	// this->_exp = 0;
	// this->_idLooser = idPlayer;
	// this->trameEndBattle();
	return (true);
      }
  return (false);
}

void					Battle::setSuccess(bool const val)
{
  this->_success = val;
}

void					Battle::trameSpell(unsigned int const idPlayer,
							   Spell const *spell,
							   unsigned int const launcher,
							   unsigned int const target) const
{
  Server::getInstance()->callProtocol<unsigned int, Spell const *, unsigned int, unsigned int>("SPELL", idPlayer, this->_id, spell, launcher, target);
}

void					Battle::trameSwitch(unsigned int const idPlayer, unsigned int const target, unsigned int const newmob, unsigned int const player) const
{
  Server::getInstance()->callProtocol<unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", idPlayer, this->_id, target, newmob, player);
}

void					Battle::trameSpellEffect(unsigned int const idPlayer,
								 unsigned int const idMob, 
								 int const hpChange) const
{
  Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("SPELLEFFECT", idPlayer, this->_id, hpChange, idMob);
}

void					Battle::trameDeadMob(unsigned int const idPlayer, unsigned int const idMob) const
{
  Server::getInstance()->callProtocol<unsigned int, unsigned int>("DEADMOB", idPlayer, this->_id, idMob);
}

void					Battle::trameCapture(unsigned int const idPlayer, unsigned int const idMob, bool const success) const
{
  Server::getInstance()->callProtocol<unsigned int, bool>("CAPTUREEFFECT", idPlayer, idMob, success);
}

void					Battle::trameLaunchBattle(unsigned int const idPlayer, Player *player) const
{
  Server::getInstance()->callProtocol<unsigned int const, Player const *, unsigned int const>("LAUNCHBATTLE", idPlayer, this->_id, player, this->_mobNumber);
}

void					Battle::trameTurnTo(unsigned int const idPlayer, unsigned int const idMob) const
{
  Server::getInstance()->callProtocol<unsigned int>("TURNTO", idPlayer, idMob);
}

void					Battle::trameEndBattle()
{
  for (auto it = this->_players.begin(); it != this->_players.end(); ++it)
    {
      if ((*it)->getType() == Player::PlayerType::PLAYER)
	{
	  Server::getInstance()->callProtocol<unsigned int, bool, unsigned int, unsigned int, std::list<AItem *> *>("ENDBATTLE", (*it)->getUser().getId(), this->_id, ((*it)->getId() == this->_idLooser)?(false):(true), this->_money, this->_exp, NULL);
  	  ClientManager::getInstance()->endBattle((*it)->getUser().getId());
	}
    }
}

bool					compareSpeed(Mob *mob1, Mob *mob2)
{
  Stat::value_type			speed1 = mob1->getCurrentStat("Speed");
  Stat::value_type			speed2 = mob2->getCurrentStat("Speed");

  if (speed1 < speed2)
    return (true);
  else
    return (false);
}

//
// Battle.cpp for Battle in /home/maitre_c/work/linumon/MMO/Common/src/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 15:37:55 2014 antoine maitre
// Last update Mon Mar  3 04:57:19 2014 antoine maitre
//

#include				"Battle/Battle.hh"
#include				"Database/Repositories/StatKeyRepository.hpp"

Battle::Battle(unsigned int const id, eBattle const type, int const mobNumber, Player *player1, Player *player2)
  : _id(id), _type(type),
    _mobNumber(mobNumber)
{
  int i = 0;

  for (auto it = player1->getDigitaliser().getMobs().begin(); it != player1->getDigitaliser().getMobs().end() && i < mobNumber; it++)
    this->_mobs.push_back((*it));
  i = 0;
  for (auto it = player2->getDigitaliser().getMobs().begin(); it != player2->getDigitaliser().getMobs().end() && i < mobNumber; it++)
    this->_mobs.push_back((*it));
  if (player1->getType() == Player::PlayerType::PLAYER)
    this->trameLaunchBattle(player1->getId(), player2);
  if (player2->getType() == Player::PlayerType::PLAYER)
    this->trameLaunchBattle(player2->getId(), player1);
  this->_players.push_back(player1);
  this->_players.push_back(player2);
  this->_mobs.sort(compareSpeed);
  this->next();
}

Battle::~Battle()
{
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    {
      if ((*it)->getType() == Player::PlayerType::PLAYER)
	ClientManager::getInstance()->endBattle((*it)->getId());
    }
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
  static StatKey const			*hpKey = Database::getRepository<StatKey>().getByName("HP");
  Stats const				*statMob;
  int					i;

  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    {
      i = 0;
      for (auto itb = this->_mobs.begin(); itb != this->_mobs.end(); itb++)
	{
	  statMob = &(*it)->getStats();
	  if ((*it)->isMyMob((*it)->getId()) && statMob->getStat(*hpKey) <= 0)
	    i++;
	  if (i == _mobNumber)
	    return (true);
	}
    }
  return (false);

}

bool					Battle::spell(unsigned int const launcher, unsigned int const target, Spell *spell) //, int id_lanceur
{
  static StatKey const			*hpKey = Database::getRepository<StatKey>().getByName("HP");
  Mob					*mobLauncher;
  Mob					*mobTarget;
 
  for (auto it = this->_mobs.begin(); it != this->_mobs.end(); it++)
    {
      if ((*it)->getId() == launcher)
	mobLauncher = (*it);
      if ((*it)->getId() == target)
	mobTarget = (*it);
    }
  if (mobLauncher && mobTarget)
    {
      (*spell)(*mobLauncher, *mobTarget);
      for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	if ((*it)->getType() == Player::PlayerType::PLAYER)
	  {
	    this->trameSpell((*it)->getId(), spell, launcher, target);
	    this->trameSpellEffect((*it)->getId(), target, 10);
	  } 

      Stats statMob = mobTarget->getStats();
      if (statMob.getStat(*hpKey) <= 0)
	for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	  if ((*it)->getType() == Player::PlayerType::PLAYER)
	    this->trameDeadMob((*it)->getId(), target);
    }
  return (this->checkEnd());
}

bool					Battle::dswitch(unsigned int const target, unsigned int const newmob)
{
  for (auto itMob = this->_mobs.begin(); itMob != this->_mobs.end(); itMob++)
    if ((*itMob)->getId() == target)
      for (auto it = this->_players.begin(); it != this->_players.end(); it++)
	if ((*it)->isMyMob((*itMob)->getId()))
	  (*itMob) = (Mob *)(&(*it)->getMob(target));
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    if ((*it)->getType() == Player::PlayerType::PLAYER)
      this->trameSwitch((*it)->getId(), target, newmob);
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
	    this->_players.front()->capture(*(*it));
	    static_cast<AI *>(this->_players.back())->remove(target);
	    this->_mobs.erase(it);
	    this->trameCapture(this->_players.front()->getId(), target);
	  }
      }
  return (this->checkEnd());
}

void					Battle::next()
{
  auto tmp = this->_mobs.front();
  this->_mobs.pop_front();
  this->_mobs.push_back(tmp);
  for (auto it = this->_players.begin(); it != this->_players.end(); it++)
    if ((*it)->isMyMob(tmp->getId()))
      {
	if ((*it)->getType() == Player::PlayerType::PLAYER)
	  this->trameTurnTo((*it)->getId(), tmp->getId());
	else
	  {
	    auto tmp2 = static_cast<AI *>((*it))->action(tmp->getId());
	    this->spell(std::get<0>(tmp2), std::get<1>(tmp2), (Spell *)std::get<2>(tmp2));
	  }
      }
}

void					Battle::trameSpell(unsigned int const idPlayer,
							   Spell const *spell,
							   unsigned int const launcher,
							   unsigned int const target) const
{
  Server::getInstance()->callProtocol<unsigned int, Spell const *, unsigned int, unsigned int>("SPELL", idPlayer, this->_id, spell, launcher, target);
}

void					Battle::trameSwitch(unsigned int const idPlayer, unsigned int const target, unsigned int const newmob) const
{
  Server::getInstance()->callProtocol<unsigned int, unsigned int, unsigned int>("SWITCH", idPlayer, this->_id, target, newmob);
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

void					Battle::trameCapture(unsigned int const idPlayer, unsigned int const idMob) const
{
  Server::getInstance()->callProtocol<unsigned int, bool>("CAPTUREEFFECT", idPlayer, idMob, true);
}

void					Battle::trameLaunchBattle(unsigned int const idPlayer, Player *player) const
{
  Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", idPlayer, this->_id, player);
}

void					Battle::trameTurnTo(unsigned int const idPlayer, unsigned int const idMob) const
{
  Server::getInstance()->callProtocol<unsigned int, unsigned int>("TURNTO", idPlayer, this->_id, idMob);
}

bool					compareSpeed(Mob *mob1, Mob *mob2)
{
  static StatKey const			*speedKey = Database::getRepository<StatKey>().getByName("Speed");
  int speed1 = mob1->getStats().getStat(*speedKey);
  int speed2 = mob2->getStats().getStat(*speedKey);

  if (speed1 < speed2)
    return (true);
  else
    return (false);
}

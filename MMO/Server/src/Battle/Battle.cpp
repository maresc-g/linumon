//
// Battle.cpp for Battle in /home/maitre_c/work/linumon/MMO/Common/src/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 15:37:55 2014 antoine maitre
// Last update Wed Feb 26 01:20:05 2014 alexis mestag
//

#include				"Battle/Battle.hh"
#include				"Database/Repositories/StatKeyRepository.hpp"

Battle::Battle(unsigned int const id, eBattle const type, int const mobNumber, Player *player1, Player *player2)
  : _id(id), _type(type),
    _mobNumber(mobNumber),
    // _mobs1(),
    // _mobs2(),
    _player1(player1),
    _player2(player2)
{
  static StatKey const			*speedKey = Database::getRepository<StatKey>().getByName("Speed");

  std::cout << "a" << std::endl;
  std::list<Mob *> const *tmp = &player1->getDigitaliser().getMobs();
  Stats const *stats;

  int i = 0;
  for (auto it = tmp->begin(); it != tmp->end() && i < mobNumber; it++)
    {
      this->_mobs1.push_back((*it));
      stats = &(*it)->getStats();
      this->_order.push_back(std::tuple<int, int>((*it)->getId(), stats->getStat(*speedKey)));
      i++;
    }
  std::cout << "b" << std::endl;
  tmp = &player2->getDigitaliser().getMobs();
  i = 0;
  for (auto it = tmp->begin(); it != tmp->end() && i < mobNumber; it++)
    {
      this->_mobs2.push_back((*it));
      stats = &(*it)->getStats();
      this->_order.push_back(std::tuple<int, int>((*it)->getId(), stats->getStat(*speedKey)));
      i++;
    }
  std::cout << "c" << std::endl;
  Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", _player2->getId(), id, _player1);
  Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", _player1->getId(), id, _player2);
  std::cout << "d" << std::endl;
  this->_order.sort(compareSpeed);
  this->next();
}

Battle::~Battle()
{
  ClientManager::getInstance()->endBattle(this->_player1->getUser().getId());
  if (this->_type == Battle::PVP)
    ClientManager::getInstance()->endBattle(this->_player2->getUser().getId());
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
  int					i = 0;

  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    {
      statMob = &(*it)->getStats();
      if (statMob->getStat(*hpKey) == 0)
	i++;
    }
  if (i == 0)
    return (true);
  i = 0;
  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    {
      statMob = &(*it)->getStats();
      if (statMob->getStat(*hpKey) == 0)
	i++;
    }
  if (i == 0)
    return (true);
  else
    return (false);
}

bool					Battle::spell(unsigned int const launcher, unsigned int const target, Spell *spell) //, int id_lanceur
{
  static StatKey const			*hpKey = Database::getRepository<StatKey>().getByName("HP");

  (void)launcher;
  (void)spell;
  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    if ((*it)->getId() == target)
      {
	Stats statMob = (*it)->getStats();
	statMob.setStat(*hpKey, statMob.getStat(*hpKey) - 10);
	Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("SPELLEFFECT", this->_player1->getId(), this->_id, 10, target);
	Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("SPELLEFFECT", this->_player2->getId(), this->_id, 10, target);
	if (statMob.getStat(*hpKey) <= 0)
	  {
	    Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("DEADMOB", this->_player2->getId(), this->_id, 10, target);
	    Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("DEADMOB", this->_player1->getId(), this->_id, 10, target);
	  }
      }
  for (auto it = this->_mobs2.begin(); it != this->_mobs2.end(); it++)
    if ((*it)->getId() == target)
      {
	Stats statMob = (*it)->getStats();
	statMob.setStat(*hpKey, statMob.getStat(*hpKey) - 10);
	Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("SPELLEFFECT", this->_player1->getId(), this->_id, 10, target);
	Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("SPELLEFFECT", this->_player2->getId(), this->_id, 10, target);
	if (statMob.getStat(*hpKey) <= 0)
	  {
	    Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("DEADMOB", this->_player2->getId(), this->_id, 10, target);
	    Server::getInstance()->callProtocol<unsigned int, int, unsigned int>("DEADMOB", this->_player1->getId(), this->_id, 10, target);
	  }
      }
  return (this->checkEnd());
}

bool					Battle::dswitch(unsigned int const target, unsigned int const newmob)
{
  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    if ((*it)->getId() == target)
      {
	std::list<Mob *> const *tmp = &this->_player1->getDigitaliser().getMobs();
	for (auto itb = tmp->begin(); itb != tmp->end(); itb++)
	  if ((*itb)->getId() == newmob)
	    {
	      (*it) = (*itb);
	      Server::getInstance()->callProtocol<unsigned int, unsigned int, unsigned int>("SWITCH", this->_player2->getId(), this->_id, target, newmob);
	      return (true);
	    }
	return (false);
      }
  for (auto it = this->_mobs2.begin(); it != this->_mobs2.end(); it++)
    if ((*it)->getId() == target)
      {
	std::list<Mob *> const *tmp = &this->_player2->getDigitaliser().getMobs();
	for (auto itb = tmp->begin(); itb != tmp->end(); itb++)
	  if ((*itb)->getId() == newmob)
	    {
	      (*it) = (*itb);
	      Server::getInstance()->callProtocol<unsigned int, unsigned int, unsigned int>("SWITCH", this->_player1->getId(), this->_id, target, newmob);
	      return (true);
	    }
	return (false);
      }
  return (false);
}

bool					Battle::capture(unsigned int const target)
{
  if (this->_type == PVP)
    return (false);
  else
    {
      for (auto it = this->_mobs2.begin(); it != this->_mobs2.end(); it++)
	{
	  if ((*it)->getId() == target)
	    {
	      this->_player1->capture(*(*it));
	      this->_mobs2.erase(it);
	      delete *it;
	      Server::getInstance()->callProtocol<unsigned int, bool>("CAPTUREEFFECT", this->_player1->getId(), this->_id, true);
	      return (true);
	    }
	}
      return (false);
    }
}

void					Battle::next()
{
  Server::getInstance()->callProtocol<unsigned int const, unsigned int const>("TURNTO", this->_player1->getId(), this->_id, std::get<0>(this->_order.front()));
  auto tmp = this->_order.front();
  this->_order.pop_front();
  this->_order.push_back(tmp);
}

bool					compareSpeed(std::tuple<int, int> tuple1, std::tuple<int, int> tuple2)
{
  if (std::get<1>(tuple1) < std::get<1>(tuple2))
    return (true);
  else
    return (false);
}

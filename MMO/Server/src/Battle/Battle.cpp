//
// Battle.cpp for Battle in /home/maitre_c/work/linumon/MMO/Common/src/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 15:37:55 2014 antoine maitre
// Last update Tue Feb 11 17:04:37 2014 antoine maitre
//

#include				"Battle/Battle.hh"

Battle::Battle(unsigned int const id, eBattle const type, int const mobNumber, Player *player1, Player *player2)
  : _id(id), _type(type),
    _mobNumber(mobNumber),
    // _mobs1(),
    // _mobs2(),
    _player1(player1),
    _player2(player2)
{
  std::list<Mob *> tmp = player1->getDigitaliser().getMobs();
  int i = 0;
  for (auto it = tmp.begin(); it != tmp.end() && i < mobNumber; it++)
    {
      this->_mobs1.push_back((*it));
      Stats stats = (*it)->getStats();
      this->_order.push_back(std::tuple<int, int>((*it)->getId(), stats.getStat(Stat::eStat::SPEED)));
      i++;
    }
  tmp = player2->getDigitaliser().getMobs();
  i = 0;
  for (auto it = tmp.begin(); it != tmp.end() && i < mobNumber; it++)
    {
      this->_mobs2.push_back((*it));
      Stats stats = (*it)->getStats();
      this->_order.push_back(std::tuple<int, int>((*it)->getId(), stats.getStat(Stat::eStat::SPEED)));
      i++;
    }
  this->_order.sort(compareSpeed);
  this->next();
}

Battle::~Battle()
{
  
}


unsigned int				Battle::getID() const
{
  return (this->_id);
}

Battle::eBattle 			Battle::getType() const
{
  return (this->_type);
}

bool					Battle::spell(unsigned int const target, Spell *spell) //, int id_lanceur
{
  (void)spell;
  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    if ((*it)->getId() == target)
      {
	Stats statMob = (*it)->getStats();
	statMob.setStat(Stat::eStat::HP, statMob.getStat(Stat::eStat::HP) - 10);
      }
  for (auto it = this->_mobs2.begin(); it != this->_mobs2.end(); it++)
    if ((*it)->getId() == target)
      {
	Stats statMob = (*it)->getStats();
	statMob.setStat(Stat::eStat::HP, statMob.getStat(Stat::eStat::HP) - 10);
      }
  return (true);
}

bool					Battle::dswitch(unsigned int const target, unsigned int const newmob)
{
  for (auto it = this->_mobs1.begin(); it != this->_mobs1.end(); it++)
    if ((*it)->getId() == target)
      {
	std::list<Mob *> tmp = this->_player1->getDigitaliser().getMobs();
	for (auto itb = tmp.begin(); itb != tmp.end(); itb++)
	  if ((*itb)->getId() == newmob)
	    {
	      (*it) = (*itb);
	      return (true);
	    }
	return (false);
      }
  for (auto it = this->_mobs2.begin(); it != this->_mobs2.end(); it++)
    if ((*it)->getId() == target)
      {
	std::list<Mob *> tmp = this->_player2->getDigitaliser().getMobs();
	for (auto itb = tmp.begin(); itb != tmp.end(); itb++)
	  if ((*itb)->getId() == newmob)
	    {
	      (*it) = (*itb);
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

//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Fri Mar  7 14:46:09 2014 antoine maitre
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"

BattleUpdater::BattleUpdater()
  : Thread(), _quit(false), _mutex(new Mutex)
{
  std::string str = "CAPTURE";
  this->_mutex->init();
  //  std::cout << (& BattleUpdater::capture) << std::endl;
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::capture), this);
  //  str = "SWITCH";
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::dswitch), this);
  // str = "SPELL";
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::spell), this);
  this->create(&launch, this);
  this->start();
}

BattleUpdater::~BattleUpdater()
{
  delete _funcs;
  _mutex->destroy();
  delete _mutex;
}

void				BattleUpdater::lock()
{
  this->_mutex->lock();
}

void				BattleUpdater::unlock()
{
  this->_mutex->unlock();
}

void				BattleUpdater::addTrame(Trame trame)
{
  this->_trames.push_back(&trame);
}

void				BattleUpdater::run()
{
  this->_mutex->lock();
  while (!_quit)
    {
      if (!this->_trames.empty())
	{
	  auto tmp = this->_trames.front();
	  if (this->_trames.front()->isMember("CAPTURE"))
	    this->capture(_trames.front());
	  else if (this->_trames.front()->isMember("SPELL"))
	    this->spell(_trames.front());
	  else if (this->_trames.front()->isMember("SWITCH"))
	    this->dswitch(_trames.front());
	  this->_trames.pop_front();
	  delete tmp;
	}
      this->_mutex->unlock();
      usleep(10000);
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

bool				BattleUpdater::newBattle(Player *player1, Player *player2, unsigned int const id)
{
  if (!player2)
    {
      AI *tmp = new AI("I m going to crush you");
      int mobInBattle = rand() % 3 + 1;

      for (int i = 0; i < mobInBattle; i++)
	{
	  Mob *tmpMob = player1->getDBZone().getRandomMob();
	  tmp->capture(*tmpMob);
	  tmp->mobtoBattleMob(tmpMob->getId());
	}
      tmp->addEnemy(player1->getDigitaliser().getMobs());
      this->_battles.push_back(new Battle(id, Battle::PVP, mobInBattle, player1, tmp));
    }
  else
    new Battle(id, Battle::PVP, rand()%3 + 1, player1, player2);
  return (true);
}

bool				BattleUpdater::spell(Trame *trame)
{
  Spell				*spell = Spell::deserialization((*trame)((*trame)["SPELL"]["SPELL"]));
  Battle			*tmp = NULL;

  for (auto it = this->_battles.begin(); it != this->_battles.end(); it++)
    if ((*it)->getID() == (*trame)["SPELL"]["IDBATTLE"].asUInt())
      if ((*it)->spell((*trame)["SPELL"]["LAUNCHER"].asUInt(), (*trame)["SPELL"]["TARGET"].asUInt(), spell))
	tmp = (*it);
  if (tmp)
    {
      this->_battles.remove(tmp);
      delete tmp;
    }
  return (true);
}

bool				BattleUpdater::capture(Trame *trame)
{
  for (auto it = this->_battles.begin(); it != this->_battles.end(); it++)
    if ((*it)->getID() == (*trame)["CAPTURE"]["IDBATTLE"].asUInt())
      {
	(*it)->capture((*trame)["CAPTURE"]["TARGET"].asInt());
	if ((*it)->checkEnd())
	  {
	    this->_battles.remove((*it));
	    delete (*it);
	    break;
	  }
      }
  return (true);
}

bool				BattleUpdater::dswitch(Trame *trame)
{
  for (auto it = this->_battles.begin(); it != this->_battles.end(); it++)
    if ((*it)->getID() == (*trame)["SWITCH"]["IDBATTLE"].asUInt())
      (*it)->dswitch((*trame)["SWITCH"]["TARGET"].asInt(), (*trame)["SWITCH"]["NEWMOB"].asInt());
  return (true);
}

std::list<Battle *>		BattleUpdater::getBattles() const
{
  return (this->_battles);
}

int				BattleUpdater::getNumOfBattle() const
{
  return (this->_battles.size());
}

void				BattleUpdater::disconnect(unsigned int const idPlayer)
{
  for (auto it = this->_battles.begin(); it != this->_battles.end(); it++)
    {
      if ((*it)->isInThisBattle(idPlayer))
	{
	  this->_battles.remove((*it));
	  delete (*it);
	  break;
	}
    }
}

void				*launch(void *data)
{
  if (data)
    {
      BattleUpdater		*tmp = reinterpret_cast<BattleUpdater *>(data);

      tmp->run();
    }
  return (NULL);
}

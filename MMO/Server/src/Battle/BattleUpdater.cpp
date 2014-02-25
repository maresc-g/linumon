//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Tue Feb 25 17:04:27 2014 antoine maitre
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"

BattleUpdater::BattleUpdater()
  : Thread(), _quit(false), _mutex(new Mutex), _funcs(new std::map<std::string, funcBattle>)
{
  std::string str = "CAPTURE";
  this->_mutex->init();
  (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::capture), this);
   str = "SWITCH";
  (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::dswitch), this);
  str = "SPELL";
  (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::spell), this);
  this->create(&launch, this);
  this->start();
}

BattleUpdater::~BattleUpdater()
{
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
	  for (auto it = this->_funcs->begin(); it != this->_funcs->end(); it++)
	    if (this->_trames.front()->isMember(it->first))
	      {
		auto tmp = this->_trames.front();
		((*this->_funcs)[it->first])(tmp);
		this->_trames.pop_front();
		delete tmp;
	      }
	}
      this->_mutex->unlock();
      usleep(10000);
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

bool				BattleUpdater::newBattle(Player *player1, Player *player2)
{
  unsigned int			id = 0;

  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->getID() != id)
	{
	  // if (player2->getType() == IA || player1->getType() == IA)
	  //   {
	  new Battle(id, Battle::PVE, 1, player1, player2);
	    // }
	  // else
	  //   {
	  //     new Battle(id, Battle::PVP, 1, player1, player2);
	  //     Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", player1->getId(), id, player2);
	  //   }
	}
    }
  return (true);
}

bool				BattleUpdater::spell(Trame *trame)
{
  Spell				*spell = Spell::deserialization((*trame)((*trame)["SPELL"]["SPELL"]));
  Battle			*tmp = NULL;

  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    if ((*it)->getID() == (*trame)["SPELL"]["IDBATTLE"].asUInt())
      if ((*it)->spell((*trame)["SPELL"]["LAUNCHER"].asUInt(), (*trame)["SPELL"]["TARGET"].asUInt(), spell))
	tmp = (*it);
  if (tmp)
    {
      this->_battles->remove(tmp);
      delete tmp;
    }
  return (true);
}

bool				BattleUpdater::capture(Trame *trame)
{
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    if ((*it)->getID() == (*trame)["CAPTURE"]["IDBATTLE"].asUInt())
      (*it)->capture((*trame)["CAPTURE"]["TARGET"].asInt());
  return (true);
}

bool				BattleUpdater::dswitch(Trame *trame)
{
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    if ((*it)->getID() == (*trame)["SWITCH"]["IDBATTLE"].asUInt())
      (*it)->dswitch((*trame)["SWITCH"]["TARGET"].asInt(), (*trame)["SWITCH"]["NEWMOB"].asInt());
  return (true);
}

std::list<Battle *>		*BattleUpdater::getBattles() const
{
  return (this->_battles);
}

int				BattleUpdater::getNumOfBattle() const
{
  return (this->_battles->size());
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

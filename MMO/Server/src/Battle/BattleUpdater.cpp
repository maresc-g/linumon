//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Tue Mar 25 16:22:56 2014 alexis mestag
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"
#include			"Loader/LoaderManager.hh"
#include			"AI/AI.hh"

BattleUpdater::BattleUpdater()
  : Thread(),
    _quit(false),
    _mutex(new Mutex),
    _trames(new std::list<std::pair<Trame *, bool> >),
    _battles(new std::list<Battle *>),
    _nbTrame(0)
{
  // std::string str = "CAPTURE";
  this->_mutex->init();
  _mutex->lock();

  Trame				*trame = NULL;
  for (int i = 0 ; i < DEFAULT_STORAGE_BATTLE ; ++i)
    {
      _trames->push_back(std::make_pair(trame, false));
    }
  _mutex->unlock();
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
  _mutex->lock();
  for (auto it = _trames->begin() ; it != _trames->end() ; ++it)
    if (it->first)
      delete it->first;
  delete _trames;
  for (auto it = _battles->begin() ; it != _battles->end() ; ++it)
    if ((*it))
      delete *it;
  delete _battles;
  _mutex->unlock();
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

void				BattleUpdater::addTrame(Trame &trame)
{
  bool				set = false;

  // _mutex->lock();
  for (auto it = _trames->begin() ; it != _trames->end() && !set ; ++it)
    {
      if (!it->second && !it->first)
	ObjectPoolManager::getInstance()->setObject(it->first, "trame");
      if (it->first && !it->second)
	{
	  it->second = true;
	  it->first->clear();
	  *it->first = trame;
	  set = true;
	  _nbTrame++;
	}
    }
  if (!set)
    {
      Trame				*tmp = NULL;

      ObjectPoolManager::getInstance()->setObject(tmp, "trame");
      *tmp = trame;
      _trames->push_back(std::make_pair(tmp, true));
      _nbTrame++;
    }
  // _mutex->unlock();
}

void				BattleUpdater::run()
{
  this->_mutex->lock();
  while (!_quit)
    {
      if (_nbTrame > 0)
	for (auto it = _trames->begin() ; it != _trames->end() ; ++it)
	  {
	    if (it->second && it->first)
	      {
		if ((*it->first)[CONTENT].isMember("CAPTURE"))
		  this->capture(&(*it->first)((*it->first)[CONTENT]));
		else if ((*it->first)[CONTENT].isMember("SPELL"))
		  this->spell(&(*it->first)((*it->first)[CONTENT]));
		else if ((*it->first)[CONTENT].isMember("SWITCH"))
		  this->dswitch(&(*it->first)((*it->first)[CONTENT]));
		it->second = false;
		_nbTrame--;
	      }
	  }
      else
	{
	  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
	    if ((*it)->checkEnd())
	      {
		std::cout << "J AI TROUVE UNE BATTLE FINIE" << std::endl;
		Battle	*b = *it;
		this->_battles->remove((*it));
		delete b;
		break;
	      }
	}
      this->_mutex->unlock();
      usleep(1000);
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
	  tmp->setStat("Limit mob", mobInBattle);
	  tmp->capture(*tmpMob, false);
	  tmp->mobtoBattleMob(tmpMob->getId());
	}
      tmp->addEnemy(player1->getDigitaliser().getBattleMobs());
      this->_battles->push_back(new Battle(id, Battle::PVE, mobInBattle, player1, tmp));
    }
  else
    this->_battles->push_back(new Battle(id, Battle::PVP, 3, player1, player2));
  return (true);
}

bool				BattleUpdater::spell(Trame *trame)
{
  /*
    if (spell)
    tu fais ce tu veux avec sauf de le modifier ou de le delete
   */
  Spell				*spell = (**LoaderManager::getInstance()->getSpellLoader())->getValue((*trame)["SPELL"]["NAME"].asString());
  Battle			*tmp = NULL;

  std::cout << "ME VOICI DANS LE SPELL" << std::endl;
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      std::cout << "Il y a bien des battles ICI" << std::endl;
      if ((*it)->getID() == (*trame)["SPELL"]["IDBATTLE"].asUInt())
	{
	  std::cout << "J AI TROUVE L IDBATTLE" << std::endl;
	  (*it)->setLauncherMob((*it)->getMobById((*trame)["SPELL"]["LAUNCHER"].asUInt()));
	  (*it)->setTargetMob((*it)->getMobById((*trame)["SPELL"]["TARGET"].asUInt()));
	  (*it)->setSpell(spell);
	  if ((*it)->spell())
	    tmp = (*it);
	  else
	    (*it)->next();
      	}
    }
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
      {
	(*it)->capture((*trame)["CAPTURE"]["TARGET"].asInt());
	if ((*it)->checkEnd())
	  {
	    this->_battles->remove((*it));
	    delete (*it);
	    break;
	  }
	else
	  (*it)->next();
      }
  return (true);
}

bool				BattleUpdater::dswitch(Trame *trame)
{
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    if ((*it)->getID() == (*trame)["SWITCH"]["IDBATTLE"].asUInt())
      {
	(*it)->dswitch((*trame)["SWITCH"]["TARGET"].asInt(), (*trame)["SWITCH"]["NEWMOB"].asInt());
	(*it)->next();
      }
  return (true);
}

std::list<Battle *>		&BattleUpdater::getBattles() const
{
  return (*this->_battles);
}

int				BattleUpdater::getNumOfBattle() const
{
  return (this->_battles->size());
}

void				BattleUpdater::disconnect(unsigned int const idPlayer)
{
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->isInThisBattle(idPlayer))
	{
	  (*it)->setSuccess(false);
	  (*it)->disconnect(idPlayer);
	  delete (*it);
	  this->_battles->remove((*it));
	  break;
	}
    }
}

void				BattleUpdater::setQuit(bool const quit)
{
  _mutex->lock();
  _quit = quit;
  _mutex->unlock();
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

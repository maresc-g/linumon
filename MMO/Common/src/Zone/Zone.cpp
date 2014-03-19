//
// Zone.cpp for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 14:01:10 2014 antoine maitre
// Last update Wed Mar 19 16:22:09 2014 cyril jourdain
//

#include			<iostream>
#include			<algorithm>
#include			"Zone/Zone.hh"

Zone::Zone(Json::Value const topography):
  Nameable(topography["Name"].asString()),
  _sizeX(topography["X"].asInt()),
  _sizeY(topography["Y"].asInt()),
  _posX(topography["POSITION"]["X"].asInt()),
  _posY(topography["POSITION"]["Y"].asInt()),
  _players(new std::list<AEntity *>),
  _cases(new std::list<Case *>)

# ifdef	SERVER
  , _dbZone(NULL)
# endif
{
  std::ostringstream		zone;

  for (int i = 1; i; i++)
    {
      zone << "Zone" << i;
      if (topography.isMember(zone.str()))
	{
	  for (int j = topography[zone.str()]["X1"].asInt(); j < topography[zone.str()]["X2"].asInt(); j++)
	    for (int k = topography[zone.str()]["Y1"].asInt(); k < topography[zone.str()]["Y2"].asInt(); k++)
	      this->_cases->push_back(new Case(j, k, topography[zone.str()]["Safe"].asBool()));
	}
      else
	break;
      zone.str("");
    }
  this->_cases->sort(compareValue);
  this->_cases->unique(sameValue);

# ifdef	SERVER
  Repository<DBZone>		*rz = Repository<DBZone>::getInstance();
  DBZone			*z = rz->getByName(this->getName());

  if (!z) {
    std::cerr << "Error : DBZone '" << this->getName() << "' doesn't exist" << std::endl;
  }

  _dbZone = z;
# endif
}

Zone::~Zone()
{
  for (auto it = this->_cases->begin() ; it != this->_cases->end() ; ++it)
    delete (*it);
  delete _cases;
}

void				Zone::addPlayer(AEntity *player)
{
  Case				*cas;
  Player			*tmp = NULL;

  this->_players->push_back(player);
  if (player->getEntityType() == AEntity::STATENTITY)
    {
      tmp = static_cast<Player *>(player);
      cas = this->getCase(tmp->getX(), tmp->getY());
      if (cas)
	cas->addAEntity(player);
      else
	this->delPlayer(player); //case n'existe pas
    }
}

void				Zone::delPlayer(AEntity *player)
{
  Case				*cas;
  Player			*tmp = NULL;

  this->_players->remove(player);
  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    (*it)->delAEntity(player->getId());
  // if (player->getEntityType() == AEntity::STATENTITY)
  //   {
  //     tmp = static_cast<Player *>(player);
  //     cas = this->getCase(tmp->getX(), tmp->getY());
  //     if (cas)
  // 	cas->delAEntity(player->getId());
  //   }
}

void				Zone::addEntity(AEntity *entity)
{
  Case				*cas;
  Ressource			*tmp;
  PNJ				*tmp1;

  if (entity->getEntityType() == AEntity::RESSOURCE)
    {
      tmp = static_cast<Ressource *>(entity);
      cas = this->getCase(tmp->getX(), tmp->getY());
    }
  else
    {
      tmp1 = static_cast<PNJ *>(entity);
      cas = this->getCase(tmp1->getX(), tmp1->getY());
    }
  if (cas)
    cas->addAEntity(entity);
}

void				Zone::delEntity(AEntity *entity)
{
  Case				*cas;
  Ressource			*tmp;

  tmp = static_cast<Ressource *>(entity);
  cas = this->getCase(tmp->getX(), tmp->getY());
  if (cas)
    cas->delAEntity(entity);
}

void				Zone::delEntity(unsigned int const id, Ressource::RessourceCoordinate const &coord)
{
  Case				*cas;

  cas = this->getCase(coord.getX(), coord.getY());
  if (cas)
    cas->delAEntity(id);
}

std::list<AEntity *>		&Zone::getPlayers() const
{
  return (*this->_players);
}

void				Zone::addCase(Case *cas)
{
  this->_cases->push_back(cas);
}

void				Zone::delCase(Case *cas)
{
  this->_cases->remove(cas);
}

Case				*Zone::getCase(int const x, int const y) const
{
  Case				*tmp;

  tmp = NULL;
  for (std::list<Case *>::iterator it = this->_cases->begin(); it != this->_cases->end(); it++)
    if ((*it)->getCoord().getX() == x && (*it)->getCoord().getY() == y)
      tmp = (*it);
  return (tmp);
}

void				Zone::cleanEntity(AEntity *entity)
{
  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    (*it)->delAEntity(entity->getId());
  for (auto it = this->_players->begin(); it != this->_players->end(); it++)
    if ((*it)->getId() == entity->getId())
      {
	this->_players->erase(it);
	break;
      }
}

std::list<Case *>		*Zone::getCases() const
{
  return (this->_cases);
}

bool				sameValue(Case *case1, Case *case2)
{
  if (case1->getCoord().getX() == case2->getCoord().getX() &&
      case1->getCoord().getY() == case2->getCoord().getY())
    {
      return (true);
    }
  return (false);
}

bool				compareValue(Case *case1, Case *case2)
{
  if (case1->getCoord().getX() < case2->getCoord().getX())
    return (true);
  if (case1->getCoord().getX() == case2->getCoord().getX() &&
      case1->getCoord().getY() < case2->getCoord().getY())
    return (true);
  else
    return (false);
}

bool				Zone::serialization(Trame &trame) const
{
  int				i = 1;

  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    if ((*it)->serialization(trame(trame[CONTENT]["MAP"][std::to_string(i)])))
      i++;
  return (true);
}

void				Zone::deserialization(Trame const &trame)
{
  std::cout << "ZONE BEGINNING" << std::endl;
  this->_players->clear();
  for (int i = 1; trame[CONTENT]["MAP"].isMember(std::to_string(i)); i++)
    {
      auto tmp = this->getCase(trame[CONTENT]["MAP"][std::to_string(i)]["X"].asInt(), trame[CONTENT]["MAP"][std::to_string(i)]["Y"].asInt());
      tmp->deserialization(trame(trame[CONTENT]["MAP"][std::to_string(i)]));
      for (auto it = tmp->getEntities()->begin(); it != tmp->getEntities()->end(); it++)
	{
	  if ((*it)->getEntityType() == AEntity::STATENTITY)
	    this->_players->push_back((*it));
	}
    }
}


int				Zone::getSizeX() const { return (_sizeX); }
int				Zone::getSizeY() const { return (_sizeY); }
int				Zone::getPosX() const { return (_posX); }
int				Zone::getPosY() const { return (_posY); }

bool				Zone::move(AEntity *entity)
{
  auto map = Map::getInstance();
  auto player = static_cast<Player *>(entity);

  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    (*it)->delAEntity(entity->getId());
  if (player->getX() >= map->getZone(player->getZone())->getSizeX() ||
      player->getY() >= map->getZone(player->getZone())->getSizeY() ||
      player->getX() <= -1 ||
      player->getY() <= -1)
    {
      Zone *tmp = NULL;
      // Move zone right
      if (player->getX() >= map->getZone(player->getZone())->getSizeX())
	{
	  tmp = map->getZoneByPos(map->getZone(player->getZone())->getPosX() + 1,
				  map->getZone(player->getZone())->getPosY());
	  if (tmp)
	    {
	      Player::Coordinate::type const x = 0;
	      player->setX(x);
	      map->changeZone(player->getZone(), tmp->getName(), entity);
	      player->setZone(tmp->getName());
	      return (true);
	    }
	  else
	    {
	      Player::Coordinate::type const x = map->getZone(player->getZone())->getSizeX();
	      player->setX(x);
	      this->getCase(player->getX(), player->getY())->addAEntity(entity);
	      return (false);
	    }
	}
      // Move zone up
      else if (player->getY() >= map->getZone(player->getZone())->getSizeY())
	{
	  tmp = map->getZoneByPos(map->getZone(player->getZone())->getPosX(),
				  map->getZone(player->getZone())->getPosY() + 1);
	  if (tmp)
	    {
	      Player::Coordinate::type const y = 0;
	      player->setY(y);
	      map->changeZone(player->getZone(), tmp->getName(), entity);
	      player->setZone(tmp->getName());
	      return (true);
	    }
	  else
	    {
	      Player::Coordinate::type const y = map->getZone(player->getZone())->getSizeY();
	      player->setY(y);
	      this->getCase(player->getX(), player->getY())->addAEntity(entity);
	      return (false);
	    }
	}

      // Move zone down
      else if (player->getY() <= -1)
	{
	  tmp = map->getZoneByPos(map->getZone(player->getZone())->getPosX(),
				  map->getZone(player->getZone())->getPosY() - 1);
	  if (tmp)
	    {
	      Player::Coordinate::type const y = tmp->getSizeY() - 1;
	      player->setY(y);
	      map->changeZone(player->getZone(), tmp->getName(), entity);
	      player->setZone(tmp->getName());
	      return (true);
	    }
	  else
	    {
	      Player::Coordinate::type const y = 0;
	      player->setY(y);	
	      this->getCase(player->getX(), player->getY())->addAEntity(entity);
	      return (false);
	    }
	}

      // Move zone left
      else if (player->getX() <= -1)
	{
	  tmp = map->getZoneByPos(map->getZone(player->getZone())->getPosX() - 1,
				  map->getZone(player->getZone())->getPosY());
	  if (tmp)
	    {
	      Player::Coordinate::type const x = tmp->getSizeX() - 1;
	      player->setX(x);
	      map->changeZone(player->getZone(), tmp->getName(), entity);
	      player->setZone(tmp->getName());
	      return (true);
	    }
	  else
	    {
	      Player::Coordinate::type const x = 0;
	      player->setX(x);
	      this->getCase(player->getX(), player->getY())->addAEntity(entity);
	      return (false);
	    }
	}
    }
  else
    this->getCase(player->getX(), player->getY())->addAEntity(entity);
  return (false);
}

#ifdef	SERVER
DBZone const			&Zone::getDBZone() const
{
  return (*_dbZone);
}

void				Zone::setDBZone(DBZone const &dbZone)
{
  _dbZone = &dbZone;
}
#endif

//
// Case.cpp for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:44:31 2014 antoine maitre
// Last update Fri Mar  7 15:34:07 2014 laurent ansel
//

#include		"Zone/Case.hh"
#include		"Loader/LoaderManager.hh"

Case::Case(int const x, int const y, bool const safe) :
  _entities(new std::list<AEntity *>),
  _coord(x, y),
  _safe(safe)
{

}

Case::~Case()
{
  delete _entities;
}

bool			Case::getSafe() const
{
  return (this->_safe);
}

const Coordinate<int>	&Case::getCoord() const
{
  return (this->_coord);
}

std::list<AEntity *>	*Case::getEntities() const
{
  return (this->_entities);
}

void			Case::addAEntity(AEntity *entity)
{
  this->_entities->push_back(entity);
}

void			Case::delAEntity(AEntity *entity)
{
  this->_entities->remove(entity);
}

void			Case::delAEntity(unsigned int const id)
{
  bool			set = false;

  for (auto it = _entities->begin() ; !set && it != _entities->end() ; ++it)
    if ((*it)->getId() == id)
      {
	it = _entities->erase(it);
	set = true;
      }
}

bool			Case::serialization(Trame &trame) const
{
  if (!this->_entities->empty())
    {
      trame["X"] = this->_coord.getX();
      trame["Y"] = this->_coord.getY();
      int i = 0;
      for (auto it = this->_entities->begin(); it != this->_entities->end(); it++)
  	{
	  if ((*it)->getEntityType() == AEntity::STATENTITY)
	    {
	      auto tmp = static_cast<Player *>(*it);
	      trame[std::to_string(i)]["PLAYER"]["ID"] = static_cast<int>(tmp->getId());
	      trame[std::to_string(i)]["PLAYER"]["NAME"] = tmp->getName();
	      trame[std::to_string(i)]["PLAYER"]["TYPE"] = tmp->getStatEntityType();
	      trame[std::to_string(i)]["PLAYER"]["ZONE"] = tmp->getZone();
	      tmp->getCoord().serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	      tmp->getFaction().serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	      if (tmp->getGuild())
		tmp->getGuild()->serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	    }
	  else if ((*it)->getEntityType() == AEntity::RESSOURCE)
	    {
	      auto tmp = static_cast<Ressource *>(*it);
	      trame[std::to_string(i)]["RES"] = tmp->getName();
	      tmp->getCoord().serialization(trame(trame[std::to_string(i)]));
	      //	      tmp->serialization(trame(trame[std::to_string(i)]));
	    }
	  else
	    {
	      auto tmp = static_cast<PNJ *>(*it);
	      trame[std::to_string(i)]["NAME"] = tmp->getName();
	      tmp->getCoord().serialization(trame(trame[std::to_string(i)]));

	      // tmp->serialization(trame(trame[std::to_string(i)]));
	    }
	  i++;
  	}
      return (true);
    }
  return (false);
}

void			Case::deserialization(Trame const &trame)
{
  Ressource		*item;
  Heal			*heal;

  for (int i = 0; trame.isMember(std::to_string(i)); i++)
    {
      if (trame[std::to_string(i)].isMember("PLAYER"))
	{
	  Player *player = new Player(trame[std::to_string(i)]["PLAYER"]["NAME"].asString());
	  player->setId(trame[std::to_string(i)]["PLAYER"]["ID"].asUInt());
	  //	  player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame[std::to_string(i)]["PLAYER"]["TYPE"].asInt()));
	  player->setCoord(*Player::PlayerCoordinate::deserialization(trame(trame[std::to_string(i)]["PLAYER"])));
	  player->setFaction(*Faction::deserialization(trame(trame[std::to_string(i)]["PLAYER"])));
	  player->setGuild(*Guild::deserialization(trame(trame[std::to_string(i)]["PLAYER"])));
	  player->setZone((trame[std::to_string(i)]["PLAYER"]["ZONE"].asString()));
	  this->_entities->push_back(player);
	}
      else if (trame[std::to_string(i)].isMember("RES"))
	{
	  item = (**LoaderManager::getInstance()->getRessourceLoader())->getValue(trame[std::to_string(i)]["RES"].asString());//Ressource::deserialization(trame(trame[std::to_string(i)])));
	  if (item)
	    {
	      item->setCoord(*Ressource::RessourceCoordinate::deserialization(trame(trame[std::to_string(i)])));
	      this->_entities->push_back(item);
	    }
	}
      else
	{
	  heal = (**LoaderManager::getInstance()->getHealLoader())->getValue(trame[std::to_string(i)]["NAME"].asString());
	  if (heal)
	    {
	      heal->setCoord(*Ressource::RessourceCoordinate::deserialization(trame(trame[std::to_string(i)])));
	      this->_entities->push_back(heal);
	    }
	}
    }
}

//
// RessourcesSpriteLoader.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar 15 23:17:56 2014 cyril jourdain

//

#include			<algorithm>
#include			<stdexcept>
#include			"SFML/RessourcesSpriteLoader.hh"

RessourcesSpriteLoader::RessourcesSpriteLoader(WindowManager *wMan) :
  _wMan(wMan), _loadMap(new RessourceLoadMap()),
  _layers(new LayerList())
{
  _layers->push_back(new Layer());
  _layers->push_back(new Layer());
  (*_loadMap)["Tree"] = &RessourcesSpriteLoader::treeLoader;
  (*_loadMap)["Healer"] = &RessourcesSpriteLoader::healerLoader;
}

RessourcesSpriteLoader::~RessourcesSpriteLoader()
{
}

void				RessourcesSpriteLoader::loadRessources()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());
  std::list<AEntity*>	*list;
  RessourceSprite	*tmp;
  sf::Vector2i		*pos = new sf::Vector2i(0,0);
  std::string		*name;

  for (int y = 0; y < zone->getSizeY(); y++)
    {
      for (int x = 0; x < zone->getSizeX(); x++)
	{
	  list = zone->getCase(x,y)->getEntities();
	  if (list && list->size() > 0)
	    {
	      for (auto it = list->begin(); it != list->end(); ++it)
		{
		  std::cout << "RESSOURCE NAME : " << (*it)->getName() << std::endl;
		  if ((*it)->getEntityType() == AEntity::RESSOURCE)
		    {
		      std::cout << "Adding at pos : "
				<< static_cast<Ressource *>(*it)->getX() << " / "
				<< static_cast<Ressource *>(*it)->getY()
				<< "WHERE"
				<< x << "/" << y << std::endl;
		    }
		  if ((*it)->getEntityType() == AEntity::RESSOURCE ||
		      (*it)->getEntityType() == AEntity::PNJ)
		    {
		      try {
			name = new std::string((*it)->getName());
			name->erase(std::remove_if(name->begin(), name->end(), [&](char const c){
			      return (isdigit(c));
			    }), name->end());
			(this->*(_loadMap->at(*name)))((*it));
		      }
		      catch (std::out_of_range const &e) {
			defaultLoader((*it));
			continue;
		      }
		    }
		  // if ((*it)->getName() == "Tree")
		  // 	{
		  // 	  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
		  // 	  if (!_sfmlView->getSpriteManager()->copySprite("tree_trunk", *tmp))
		  // 	    continue;
		  // 	  tmp->play("default");
		  // 	  tmp->setPosition(pos->x * CASE_SIZE,
		  // 			   pos->y * CASE_SIZE);
		  // 	  tmp->setPos(pos->x,
		  // 		      pos->y);
		  // 	  _entities->push_back(tmp);
		  // 	  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
		  // 	  if (!_sfmlView->getSpriteManager()->copySprite("tree_top", *tmp))
		  // 	    continue;
		  // 	  tmp->play("default");
		  // 	  tmp->setPosition(pos->x * CASE_SIZE- 64,
		  // 			   pos->y * CASE_SIZE - 128);
		  // 	  tmp->setPos(pos->x,
		  // 		      pos->y);
		  // 	  _topLayer->push_back(tmp);
		  // 	}
		  // else
		  // 	{
		  // 	  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
		  // 	  if (!_sfmlView->getSpriteManager()->copySprite((*it)->getName(), *tmp))
		  // 	    continue;
		  // 	  tmp->play("default");
		  // 	  tmp->setPosition(pos->x * CASE_SIZE,
		  // 			   pos->y * CASE_SIZE);
		  // 	  tmp->setPos(pos->x,
		  // 		      pos->y);
		  // 	  _entities->push_back(tmp);
		  // 	}
		  // }
		}
	    }
	}
    }

}

void				RessourcesSpriteLoader::drawLayer(unsigned int layerId)
{
  for (auto it = (*_layers)[layerId]->begin(); it != (*_layers)[layerId]->end(); ++it)
    {
      (*it)->update(*_wMan->getSFMLView()->getMainClock());
      _wMan->getSFMLView()->draw(**it);
      // std::cout << "Draw entitie at " << (*it)->getPosition().x << "/" << (*it)->getPosition().y << std::endl;
    }
  // std::cout << std::endl;
}

void				RessourcesSpriteLoader::onMouseEvent(QMouseEvent *event)
{
  sf::Vector2f	v = _wMan->getSFMLView()->mapPixelToCoords(sf::Vector2i(event->x(), event->y()));

  for (auto it = (*_layers)[0]->begin(); it != (*_layers)[0]->end(); ++it) {
    if ((*it)->isVisible())
      {
    	if ((*it)->isClicked(v.x, v.y))
    	  {
    	    (*it)->onClick(event);
    	    return;
    	  }
      }  
  }
}

void				RessourcesSpriteLoader::defaultLoader(AEntity *en)
{
  RessourceSprite *tmp = new RessourceSprite(static_cast<Ressource*>(en));
  sf::Vector2i		*pos = new sf::Vector2i(0,0);

  pos->x = static_cast<Ressource*>(en)->getX();
  pos->y = static_cast<Ressource*>(en)->getY();
  if (!_wMan->getSFMLView()->getSpriteManager()->copySprite((en)->getName(), *tmp))
    return;
  tmp->play("default");
  tmp->setPosition(pos->x * CASE_SIZE,
		   pos->y * CASE_SIZE);
  tmp->setPos(pos->x,
	      pos->y);
  (*_layers)[0]->push_back(tmp);
}

void				RessourcesSpriteLoader::treeLoader(AEntity *en)
{
  Sprite *tmp = new RessourceSprite(static_cast<Ressource*>(en));

  sf::Vector2i		*pos = new sf::Vector2i(0,0);
  pos->x = static_cast<Ressource*>(en)->getX();
  pos->y = static_cast<Ressource*>(en)->getY();

  if (!_wMan->getSFMLView()->getSpriteManager()->copySprite("tree_trunk", *tmp))
    return;
  tmp->play("default");
  tmp->setPosition(pos->x * CASE_SIZE,
		   pos->y * CASE_SIZE);
  tmp->setPos(pos->x,
	      pos->y);
  (*_layers)[0]->push_back(tmp);
  tmp = new RessourceSprite(static_cast<Ressource*>(en));
  if (!_wMan->getSFMLView()->getSpriteManager()->copySprite("tree_top", *tmp))
    return;
  tmp->play("default");
  tmp->setPosition(pos->x * CASE_SIZE- 64,
		   pos->y * CASE_SIZE - 128);
  tmp->setPos(pos->x,
	      pos->y);
  (*_layers)[1]->push_back(tmp);
  delete pos;
}

void				RessourcesSpriteLoader::healerLoader(AEntity *en)
{
  Sprite *tmp = new Sprite();
  sf::Vector2i		*pos = new sf::Vector2i(0,0);

  pos->x = static_cast<PNJ*>(en)->getX();
  pos->y = static_cast<PNJ*>(en)->getY();
  if (!_wMan->getSFMLView()->getSpriteManager()->copySprite("Healer", *tmp))
    return;
  tmp->play("default_down");
  tmp->setPosition(pos->x * CASE_SIZE,
		   pos->y * CASE_SIZE);
  std::cout << "HEALER POS : " << pos->x << "/" << pos->y << std::endl;
  tmp->setPos(pos->x,
	      pos->y);
  (*_layers)[0]->push_back(tmp);
}
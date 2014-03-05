//
// ContextView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 01:15:31 2014 cyril jourdain
// Last update Wed Mar  5 14:57:23 2014 cyril jourdain
//

#include		"SFML/ContextView.hh"


ContextView::ContextView(SFMLView *v, WindowManager *w) :
  _sfmlView(v), _wMan(w), _spriteMap(new SpriteMap()), _backgroundTexture(new sf::RenderTexture()),
  _backgroundSprite(new sf::Sprite())
{
}

ContextView::~ContextView()
{
}


void			ContextView::loadBackgroundMap()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());
  std::list<AEntity*>	*list;

  for (int y = 0; y < zone->getSizeY(); y++)
    {
      for (int x = 0; x < zone->getSizeX(); x++)
	{
	  if (zone->getCase(x,y) && zone->getCase(x,y)->getSafe())
	    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grass");
	  else
	    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grass"); // Play rock
	  ((*_spriteMap)[y])[x]->play("default");
	  // list = zone->getCase(x,y)->getEntities();
	  // if (list && list->size() > 0)
	  //   {
	  //     for (auto it = list->begin(); it != list->end(); it++)
	  // 	{
	  // 	  if ((*it)->getEntityType() == AEntity::RESSOURCE) {
	  // 	    _entities->push_back(new RessourceSprite(static_cast<Ressource*>(*it)));
	  // 	    _sMan->copySprite(static_cast<Ressource*>(*it)->getName(), *_entities->back());
	  // 	    _entities->back()->play("default");
	  // 	    _entities->back()->setPosition(static_cast<Ressource*>(*it)->getX() * CASE_SIZE,
	  // 					   static_cast<Ressource*>(*it)->getY() * CASE_SIZE);
	  // _entities->back()->setPos(static_cast<Ressource*>(*it)->getX(),
 	  // 					   static_cast<Ressource*>(*it)->getY());
	  // 	  }
	  // 	}
	  //   }
	}
    }

}

void			ContextView::loadBackgroundSprite()
{
  _backgroundTexture->clear(sf::Color(0,0,0));
  for (unsigned int y = 0; y != _spriteMap->size(); ++y)
    {
      for (unsigned int x = 0; x != (*_spriteMap)[y].size(); ++x)
	{
	  (*_spriteMap)[y][x]->setPosition(x * CASE_SIZE, y * CASE_SIZE);
	  (*_spriteMap)[y][x]->update(*(_sfmlView->getMainClock()));
	  _backgroundTexture->draw(*((*_spriteMap)[y][x]));
	}
    }
  _backgroundTexture->display();
}

void			ContextView::resetPOV()
{
}

void			ContextView::centerView()
{
}

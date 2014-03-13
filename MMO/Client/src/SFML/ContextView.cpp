//
// ContextView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 01:15:31 2014 cyril jourdain
// Last update Thu Mar 13 12:46:07 2014 cyril jourdain
//

#include		"SFML/ContextView.hh"
#include <cstdlib>


ContextView::ContextView(SFMLView *v, WindowManager *w) :
  _sfmlView(v), _wMan(w), _spriteMap(new SpriteMap()), _backgroundTexture(NULL),
  _backgroundSprite(NULL)
{
}

ContextView::~ContextView()
{
}


void			ContextView::loadBackgroundMap()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());

  srand(time(NULL));
  for (int y = 0; y < zone->getSizeY(); y++)
    {
      for (int x = 0; x < zone->getSizeX(); x++)
	{
	  // std::cout << x << "/" << y << std::endl;
	  //int rnd = rand() % 100;
	  if (zone->getCase(x,y) && !zone->getCase(x,y)->getSafe())
	    {
	      // if (rnd < 85)
	      ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grass");
	      // else if (rnd >= 85 && rnd <= 92)
	      // 	((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("flower");
	      // else
	      // 	((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("mushroom");
	    }
	  else
	    {
	      if (zone->getCase(x,y-1) && zone->getCase(x,y-1)->getSafe() &&
		  zone->getCase(x,y+1) && !zone->getCase(x,y+1)->getSafe())
		{
		  if (zone->getCase(x-1,y) && !zone->getCase(x-1,y)->getSafe())
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grasstodirt_downleft");
		  else if (zone->getCase(x+1,y) && !zone->getCase(x+1,y)->getSafe())
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grasstodirt_downright");
		  else
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_up");
		}
	      else if (zone->getCase(x,y-1) && !zone->getCase(x,y-1)->getSafe() &&
		       zone->getCase(x,y+1) && zone->getCase(x,y+1)->getSafe())
		{
		  if (zone->getCase(x-1,y) && !zone->getCase(x-1,y)->getSafe())
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grasstodirt_upleft");
		  else if (zone->getCase(x+1,y) && !zone->getCase(x+1,y)->getSafe())
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grasstodirt_upright");
		  else
		    ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_down");
		}
	      else if (zone->getCase(x - 1,y) && !zone->getCase(x - 1,y)->getSafe() &&
		       zone->getCase(x + 1,y) && zone->getCase(x + 1,y)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_right");
	      else if (zone->getCase(x + 1,y) && !zone->getCase(x + 1,y)->getSafe() &&
		       zone->getCase(x - 1,y) && zone->getCase(x - 1,y)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_left");
	      else if (zone->getCase(x+1,y - 1) && zone->getCase(x+1,y - 1)->getSafe() &&
		       zone->getCase(x-1,y+1) && !zone->getCase(x-1,y+1)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_upright");
	      else if (zone->getCase(x-1,y - 1) && zone->getCase(x-1,y - 1)->getSafe() &&
		       zone->getCase(x+1,y+1) && !zone->getCase(x+1,y+1)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_upleft");
	      else if (zone->getCase(x-1,y-1) && !zone->getCase(x-1,y-1)->getSafe() &&
		       zone->getCase(x+1,y+1) && zone->getCase(x+1,y+1)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_downright");
	      else if (zone->getCase(x+1,y-1) && !zone->getCase(x+1,y-1)->getSafe() &&
		       zone->getCase(x-1,y+1) && zone->getCase(x-1,y+1)->getSafe())
		((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirttograss_downleft");
	      else
	  	((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("dirt");
	    }
	  ((*_spriteMap)[y])[x]->play("default");
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

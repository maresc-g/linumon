//
// BattleView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 18:11:57 2014 cyril jourdain
// Last update Fri Mar  7 13:21:00 2014 cyril jourdain
//

#include		"SFML/BattleView.hh"
#include		"Entities/Digitaliser.hh"

BattleView::BattleView(SFMLView *v, WindowManager *w) :
  ContextView(v,w), _playerList(new std::list<OPlayerSprite*>()),
  _enemyList(new std::list<OPlayerSprite*>()), _playingMob(NULL), _selectedMob(NULL),
  _selection(new Sprite()),
  _spellSprite(new Sprite()), _spellSpriteCase(new Sprite())
{
}

BattleView::~BattleView()
{
}

void			BattleView::onInit()
{
  std::list<Mob*>	mobs = (**(_wMan->getMainPlayer()))->getDigitaliser().getMobs();
  std::list<Mob*>	enemyMobs = (**_wMan->getBattle())->getEnemy().getDigitaliser().getBattleMobs();
  int			posY = 2 * CASE_SIZE;
  int			limit = 0;

  _backgroundTexture->create(BATTLE_SIZE * CASE_SIZE, BATTLE_SIZE*CASE_SIZE);
  resetPOV();
  loadBackgroundMap();
  loadBackgroundSprite();
  for (auto it = mobs.begin(); it != mobs.end() && limit < 3; ++it)
    {
      _playerList->push_back(new OPlayerSprite((static_cast<Mob*>(*it))->getName(),
					       _sfmlView->getFont()));
      _sfmlView->getSpriteManager()->copySprite("perso1", *_playerList->back());
      _playerList->back()->play("default_up");
      _playerList->back()->generateOffset();
      _playerList->back()->setPosition(posY, ((BATTLE_SIZE- 2) * CASE_SIZE) - _playerList->back()->getCurrentBound()->height / 2 + 4);
      _playerList->back()->setPos(posY / CASE_SIZE, BATTLE_SIZE - 2);
      posY += 3*CASE_SIZE;
      limit++;
    }
  posY = 0;
  for (auto it = enemyMobs.begin(); it != enemyMobs.end(); ++it)
    {
      _enemyList->push_back(new OPlayerSprite((static_cast<Mob*>(*it))->getName(),
					       _sfmlView->getFont()));
      _sfmlView->getSpriteManager()->copySprite("perso1", *_enemyList->back());
      _playerList->back()->play("default_up");
      _playerList->back()->generateOffset();
      _playerList->back()->setPosition(posY, ((2) * CASE_SIZE) - _playerList->back()->getCurrentBound()->height / 2 + 4);
      _playerList->back()->setPos(posY / CASE_SIZE, 2);
      posY += 3*CASE_SIZE;
    }
  _playingMob = _playerList->front();
  _sfmlView->getSpriteManager()->copySprite("selectedPlayer", *_selection);
  _sfmlView->getSpriteManager()->copySprite("Lance-Flamme", *_spellSprite);
  _sfmlView->getSpriteManager()->copySprite("translucentCase", *_spellSpriteCase);
  _selection->play("default_down");
  _spellSprite->play("mouse");
  _spellSpriteCase->play("default");
  _spellSpriteCase->setVisible(false);
  (*_spellSprite)["mouse"]->setFrameLength(120000);
  (*_selection)["default_down"]->setFrameLength(45000);
}
void			BattleView::onUpdate()
{
  _selection->setPosition((_playingMob->getPosition().x), (_playingMob->getPosition().y - CASE_SIZE));
  _selection->update(*_sfmlView->getMainClock());
  _spellSprite->update(*_sfmlView->getMainClock());
  _spellSpriteCase->update(*_sfmlView->getMainClock());
}

void			BattleView::onKeyEvent(sf::Event const &event)
{
}

void			BattleView::onMouseEvent(QMouseEvent *event)
{
  bool			found = false;

  if (event->button() == Qt::NoButton)
    {
      sf::Vector2f v = _sfmlView->mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
      _spellSprite->setPosition(v.x, v.y);
      for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
	{
	  if ((*it)->isClicked(v.x, v.y))
	    {
	      // _spellSpriteCase->setPosition((static_cast<int>(static_cast<int>(v.x) / CASE_SIZE))
	      // 				    *CASE_SIZE,
	      // 				    (static_cast<int>(static_cast<int>(v.y) / CASE_SIZE))
	      // 				    *CASE_SIZE);
	      _selectedMob = (*it);
	      _spellSpriteCase->setPosition((*it)->getPos()->x * CASE_SIZE,
					    (*it)->getPos()->y * CASE_SIZE);
	      _spellSpriteCase->setVisible(true);
	      found = true;
	    }
	}
      if (!found)
	{
	  _spellSpriteCase->setVisible(false);
	  _selectedMob = NULL;
	}

    }
  if (event->button() == Qt::LeftButton)
    {
      if (_selectedMob)
	_selectedMob->onClick();
    }
}

void			BattleView::resetView()
{
}

void			BattleView::drawView()
{
  _backgroundSprite->setTexture(_backgroundTexture->getTexture());
  _sfmlView->draw(*_backgroundSprite);
  _sfmlView->draw(*_spellSpriteCase);
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(*(*it));
    }
  for (auto it = _enemyList->begin(); it != _enemyList->end(); ++it)
    {
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(*(*it));
    }
  _sfmlView->draw(*_selection);
  _sfmlView->draw(*_spellSprite);
  _sfmlView->setView(*(_sfmlView->getMainView()));
}

void			BattleView::loadBackgroundMap()
{
  for (int y = 0; y < BATTLE_SIZE; y++)
    {
      for (int x = 0; x < BATTLE_SIZE; x++)
	{
	  ((*_spriteMap)[y])[x] = _sfmlView->getSpriteManager()->copySprite("grass");
	  ((*_spriteMap)[y])[x]->play("default");
	  ((*_spriteMap)[y])[x]->setPos(x, y);
	}
    }
}

void			BattleView::resetPOV()
{
  _sfmlView->getMainView()->reset(sf::FloatRect(0,0, WIN_W,WIN_H));
  _sfmlView->getMainView()->setCenter(sf::Vector2f(BATTLE_SIZE * CASE_SIZE / 2, BATTLE_SIZE * CASE_SIZE / 2));
}

void			BattleView::centerView()
{
  _sfmlView->getMainView()->setCenter(sf::Vector2f(BATTLE_SIZE * CASE_SIZE / 2, BATTLE_SIZE * CASE_SIZE / 2));
}

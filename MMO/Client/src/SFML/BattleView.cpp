//
// BattleView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 18:11:57 2014 cyril jourdain
// Last update Wed Mar  5 15:58:12 2014 cyril jourdain
//

#include		"SFML/BattleView.hh"
#include		"Entities/Digitaliser.hh"

BattleView::BattleView(SFMLView *v, WindowManager *w) :
  ContextView(v,w), _playerList(new std::list<OPlayerSprite*>()), _ennemyList(new std::list<OPlayerSprite*>()), _playingMob(NULL), _selection(new Sprite()), _spellSprite(new Sprite())
{
}

BattleView::~BattleView()
{
}

void			BattleView::onInit()
{
  std::list<Mob*>	mobs = (**(_wMan->getMainPlayer()))->getDigitaliser().getMobs();
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
      _playerList->back()->play("default_right");
      _playerList->back()->generateOffset();
      _playerList->back()->setPosition(posY, ((BATTLE_SIZE- 2) * CASE_SIZE) - _playerList->back()->getCurrentBound()->height / 2 + 4);
      posY += 3*CASE_SIZE;
      limit++;
    }
  _playingMob = _playerList->front();
  _sfmlView->getSpriteManager()->copySprite("selectedPlayer", *_selection);
  _sfmlView->getSpriteManager()->copySprite("Lance-Flamme", *_spellSprite);
  _selection->play("default_down");
  _spellSprite->play("mouse");
  (*_spellSprite)["mouse"]->setFrameLength(50000);
  (*_selection)["default_down"]->setFrameLength(45000);
}
void			BattleView::onUpdate()
{
  _selection->setPosition((_playingMob->getPosition().x), (_playingMob->getPosition().y - CASE_SIZE));
  _selection->update(*_sfmlView->getMainClock());
}

void			BattleView::onKeyEvent(sf::Event const &event)
{
}

void			BattleView::onMouseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::NoButton)
    {
      std::cout << "move mouse" << std::endl;
    }
}

void			BattleView::resetView()
{
}

void			BattleView::drawView()
{
  _backgroundSprite->setTexture(_backgroundTexture->getTexture());
  _sfmlView->draw(*_backgroundSprite);
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(*(*it));
    }
  _sfmlView->draw(*_selection);
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

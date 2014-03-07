//
// BattleView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 18:11:57 2014 cyril jourdain
// Last update Fri Mar  7 22:19:31 2014 cyril jourdain
//

#include		<stdexcept>
#include		"SFML/BattleView.hh"
#include		"Entities/Digitaliser.hh"

BattleView::BattleView(SFMLView *v, WindowManager *w) :
  ContextView(v,w), _buttonMap(new ButtonMap), _playerList(new std::list<MobSprite*>()),
  _enemyList(new std::list<MobSprite*>()), _playingMob(NULL), _selectedMob(NULL),
  _selection(new Sprite()), _spellSprite(new Sprite()), _spellSpriteCase(new Sprite()),
  _selectedSpell("")
{
  (*_buttonMap)[Qt::NoButton] = &BattleView::noButton;
  (*_buttonMap)[Qt::LeftButton] = &BattleView::leftButton;
  (*_buttonMap)[Qt::RightButton] = &BattleView::rightButton;
}

BattleView::~BattleView()
{
}

void			BattleView::onInit()
{
  std::list<Mob*> const 	mobs = (**_wMan->getBattle())->getMobs();
  std::list<Mob*>	enemyMobs = (**_wMan->getBattle())->getEnemy().getDigitaliser().getBattleMobs();
  int			posY = 2 * CASE_SIZE;
  int			limit = 0;
  MobSprite		*tmp;

  _backgroundTexture->create(BATTLE_SIZE * CASE_SIZE, BATTLE_SIZE*CASE_SIZE);
  loadBackgroundMap();
  loadBackgroundSprite();
  for (auto it = mobs.begin(); it != mobs.end() && limit < 3; ++it)
    {
      tmp = new MobSprite((static_cast<Mob*>(*it))->getName(),
			  _sfmlView->getFont(), _wMan);
      _sfmlView->getSpriteManager()->copySprite("perso1", *tmp);
      tmp->play("default_up");
      tmp->generateOffset();
      tmp->setPosition(posY, ((BATTLE_SIZE- 2) * CASE_SIZE) - tmp->getCurrentBound()->height / 2 + 4);
      tmp->setPos(posY / CASE_SIZE, BATTLE_SIZE - 2);
      tmp->setPlayerId((*it)->getId(), false);
      tmp->setHUDInfo(*(static_cast<Mob*>(*it)));
      tmp->setInfoVisibility(false);
      _playerList->push_back(tmp);
      posY += 3*CASE_SIZE;
      limit++;
    }
  posY = 2*CASE_SIZE;
  for (auto it = enemyMobs.begin(); it != enemyMobs.end(); ++it)
    {
      tmp = new MobSprite((static_cast<Mob*>(*it))->getName(),
			  _sfmlView->getFont(), _wMan);
      _sfmlView->getSpriteManager()->copySprite("perso1", *tmp);
      tmp->play("default_down");
      tmp->generateOffset();
      tmp->setPosition(posY, ((2) * CASE_SIZE) - tmp->getCurrentBound()->height / 2 + 4);
      tmp->setPos(posY / CASE_SIZE, 2);
      tmp->setPlayerId((*it)->getId(), false);
      _enemyList->push_back(tmp);
      posY += 3*CASE_SIZE;
    }
  _playingMob = NULL;
  _sfmlView->getSpriteManager()->copySprite("selectedPlayer", *_selection);
  _sfmlView->getSpriteManager()->copySprite("Lance-Flamme", *_spellSprite);
  _sfmlView->getSpriteManager()->copySprite("translucentCase", *_spellSpriteCase);
  _selection->play("default_down");
  // _spellSprite->play("mouse");
  _spellSpriteCase->play("default");
  _spellSpriteCase->setVisible(false);
  (*_spellSprite)["mouse"]->setFrameLength(120000);
  (*_selection)["default_down"]->setFrameLength(45000);
}
void			BattleView::onUpdate()
{
  if ((!_playingMob) || (**_wMan->getBattle())->getTurnTo() != _playingMob->getPlayerId())
    {
      auto it = find_if(_playerList->begin(), _playerList->end(), [&](const MobSprite *val){
	  if (val->getPlayerId() == (**_wMan->getBattle())->getTurnTo())
	    return true;
	  return false;
	});
      if (it == _playerList->end())
	it = find_if(_enemyList->begin(), _enemyList->end(), [&](const MobSprite *val){
	    if (val->getPlayerId() == (**_wMan->getBattle())->getTurnTo())
	      return true;
	    return false;
	  });
      if (it != _enemyList->end())
	{
	  if (_playingMob)
	    _playingMob->setInfoVisibility(false);
	  _playingMob = *it;
	  _playingMob->setInfoVisibility(true);
	}
    }
  if (_playingMob)
    _selection->setPosition((_playingMob->getPosition().x), (_playingMob->getPosition().y - CASE_SIZE));
  _selection->update(*_sfmlView->getMainClock());
  _spellSprite->update(*_sfmlView->getMainClock());
  _spellSpriteCase->update(*_sfmlView->getMainClock());
}

void			BattleView::onKeyEvent(sf::Event const &)
{
}

void			BattleView::onMouseEvent(QMouseEvent *event)
{
  try{
    (this->*(_buttonMap->at(event->button())))(event);
  } catch (std::out_of_range const &e){
    std::cerr << "BattleView::onMouseEvent : Warning - Button not handled" << std::endl; 
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

void			BattleView::spellClick(std::string const &spell)
{
  if (playerTurn()) {
    if (_sfmlView->getSpriteManager()->copySprite(spell, *_spellSprite)) {
      _spellSprite->setVisible(true);
      _spellSprite->play("mouse");
      _selectedSpell = spell;
    }
  }
}

bool			BattleView::playerTurn() const
{
  std::list<Mob*> const 	mobs = (**_wMan->getBattle())->getMobs();
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if ((**_wMan->getBattle())->getTurnTo() == (*it)->getPlayerId())
	return true;
    }
  return false;
}

void			BattleView::leftButton(QMouseEvent *)
{
  std::list<Mob*>	enemyMobs = (**_wMan->getBattle())->getEnemy().getDigitaliser().getBattleMobs();
  Mob			*tmp = NULL;

  if (_selectedMob && playerTurn() && _selectedSpell != "")
    {
      _selectedMob->onClick();
      auto it = find_if(enemyMobs.begin(), enemyMobs.end(), [&](const Mob *val){
	  if (_selectedMob->getPlayerId() == val->getId())
	    return true;
	  return false;
	});
      if (it != enemyMobs.end())
	{
	  std::cout << "Enemy found in list" << std::endl;
	  tmp = *it;
	  auto it = find_if(tmp->getModel().getSpells().begin(),
			    tmp->getModel().getSpells().end(), [&](const Spell *val){
			      if (val->getName() == _spellSprite->getName())
				return true;
			      return false;
			    });
	  if (it != tmp->getModel().getSpells().end()){
	    std::cout << "Found Spell" << std::endl;
	    Client::getInstance()->spell( (**_wMan->getBattle())->getId(), **it,
					  (**_wMan->getBattle())->getTurnTo(),
					  _selectedMob->getPlayerId());
	    _selectedMob = NULL;
	    _spellSpriteCase->setVisible(false);
	    _spellSprite->setVisible(false);
	    _selectedSpell = "";
	  }
	}
    }
}

void			BattleView::rightButton(QMouseEvent *)
{
  _selectedMob = NULL;
  _selectedSpell = "";
  _spellSprite->setVisible(false);
}

void			BattleView::noButton(QMouseEvent *event)
{
  bool			found = false;

  sf::Vector2f v = _sfmlView->mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
  _spellSprite->setPosition(v.x, v.y);
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if ((*it)->isClicked(v.x, v.y))
	{
	  _selectedMob = (*it);
	  _spellSpriteCase->setPosition((*it)->getPos()->x * CASE_SIZE,
					(*it)->getPos()->y * CASE_SIZE);
	  _spellSpriteCase->setVisible(true);
	  found = true;
	}
    }
  for (auto it = _enemyList->begin(); it != _enemyList->end(); ++it)
    {
      if ((*it)->isClicked(v.x, v.y))
	{
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

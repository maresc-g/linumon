//
// BattleView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 18:11:57 2014 cyril jourdain
// Last update Tue Mar 11 15:17:44 2014 cyril jourdain
//

#include		<stdexcept>
#include		"SFML/BattleView.hh"
#include		"Entities/Digitaliser.hh"

BattleView::BattleView(SFMLView *v, WindowManager *w) :
  ContextView(v,w), _buttonMap(new ButtonMap), _playerList(new std::list<MobSprite*>()),
  _enemyList(new std::list<MobSprite*>()), _playingMob(NULL), _selectedMob(NULL),
  _selection(new Sprite()), _spellSprite(new Sprite()), _spellSpriteCase(new Sprite()),
  _selectedSpell(""), _spellUpdater(new BattleSpellUpdater(v, w)), _currentTurn(-1)
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

  if (!_spellUpdater)
    _spellUpdater = new BattleSpellUpdater(_sfmlView, _wMan);
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
      tmp->initHealthBar(*(static_cast<Mob*>(*it)));
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
      tmp->initHealthBar(*(static_cast<Mob*>(*it)));
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
  if (_currentTurn == (unsigned int)-1 || _spellUpdater->endTurn())
    {
      unsigned int turn = (**_wMan->getBattle())->getTurnTo();
      if (turn != (unsigned int) -1)
	_currentTurn = turn;
      setPlayingMob();
    }
  _spellUpdater->update(this);
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
      (*it)->resetHUDPos();
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(*(*it));
    }
  for (auto it = _enemyList->begin(); it != _enemyList->end(); ++it)
    {
      (*it)->resetHUDPos();
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(*(*it));
    }
  _sfmlView->draw(*_selection);
  _sfmlView->draw(*_spellSprite);
  _spellUpdater->draw();
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
      (static_cast<QApplication *>(QApplication::instance()))->setOverrideCursor(QCursor(Qt::BlankCursor));
      _spellSprite->setVisible(true);
      _spellSprite->play("mouse");
      _selectedSpell = spell;
    }
  }
}

std::list<MobSprite*>	*BattleView::getPlayerList() const {return _playerList; }
std::list<MobSprite*>	*BattleView::getEnemyList() const {return _enemyList; }
MobSprite		*BattleView::findMobById(unsigned int id) const
{
  auto it = find_if(_playerList->begin(), _playerList->end(), [&](const MobSprite *val){
      if (val->getPlayerId() == id)
	return true;
      return false;
    });
  if (it == _playerList->end())
    it = find_if(_enemyList->begin(), _enemyList->end(), [&](const MobSprite *val){
	if (val->getPlayerId() == id)
	  return true;
	return false;
      });
  else
    return *it;
  if (it != _enemyList->end())
    return *it;
  return NULL;
}

void			BattleView::resetHUDPos()
{
  // for (auto it = _playerList->begin(); it != _playerList->end(); it++)
  //   (*it)->resetHUDPos();
  // for (auto it = _enemyList->begin(); it != _enemyList->end(); it++)
  //   (*it)->resetHUDPos();
}

void			BattleView::setLifeVisibility(bool v)
{
  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    (*it)->setLifeVisibility(v);
  for (auto it = _enemyList->begin(); it != _enemyList->end(); it++)
    (*it)->setLifeVisibility(v);
}

void			BattleView::quitBattle()
{
  delete _buttonMap;
  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    {
      // (*it)->setInfoVisibility(false);
      delete *it;
    }
  _playerList->clear();
  for (auto it = _enemyList->begin(); it != _enemyList->end(); it++)
    delete *it;
  _enemyList->clear();
  _playingMob = NULL;
  _selectedMob = NULL;
  _spellSprite = NULL;
  _spellSpriteCase = NULL;
  _selectedSpell = "";
  delete _spellUpdater;
  _currentTurn = -1;
}

void			BattleView::setPlayingMob()
{
  // int turn = -1;
  // if (_currentTurn == -1 || _spellUpdater->endTurn())
  //   turn = (**_wMan->getBattle())->getTurnTo();

  // if (turn == -1)
  //   return;
  // else
  //   _currentTurn = turn;
  if ((!_playingMob) || _currentTurn != _playingMob->getPlayerId())
    {
      auto it = find_if(_playerList->begin(), _playerList->end(), [&](const MobSprite *val){
	  if (val->getPlayerId() == _currentTurn)
	    return true;
	  return false;
	});
      if (it != _playerList->end())
	{
	  if (_playingMob)
	    _playingMob->setInfoVisibility(false);
	  _playingMob = *it;
	  _playingMob->setInfoVisibility(true);
	}
      else
	{
	  it = find_if(_enemyList->begin(), _enemyList->end(), [&](const MobSprite *val){
	      if (val->getPlayerId() == _currentTurn)
		return true;
	      return false;
	    });
	  if (it != _enemyList->end())
	    {
	      if (_playingMob)
		_playingMob->setInfoVisibility(false);
	      _playingMob = *it;
	    }
	}
    }
}

bool			BattleView::playerTurn() const
{
  std::list<Mob*> const 	mobs = (**_wMan->getBattle())->getMobs();
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if (_currentTurn == (*it)->getPlayerId())
	return true;
    }
  return false;
}

void			BattleView::leftButton(QMouseEvent *)
{
  std::list<Mob* >	enemyMobs = (**_wMan->getBattle())->getEnemy().getDigitaliser().getBattleMobs();
  std::list<Mob* >	playerMobs = (**_wMan->getBattle())->getMobs();
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
	std::cout << "Found enemy" << std::endl;
      auto it2 = find_if(playerMobs.begin(), playerMobs.end(), [&](const Mob *val){
	  std::cout << "Mob ID : " << _playingMob->getPlayerId() << "/" << val->getId() << std::endl;
	  if (_playingMob->getPlayerId() == val->getId())
	    return true;
	  return false;
	});
      if (it2 != playerMobs.end())
	{
	  std::cout << "Found player mob" << std::endl;
	  tmp = *it2;
	  if (!tmp)
	    std::cout << "playerMob is null" << std::endl;
	  auto it3 = find_if(tmp->getModel().getSpells().begin(),
			    tmp->getModel().getSpells().end(), [&](const Spell *val){
			       if (!val)
				 {
				   std::cout << "How is that NULL ?!" << std::endl;
				   return false;
				 }
			       std::cout << "Looking in spell : " << val->getName() << std::endl;
			       if (val->getName() == _spellSprite->getName())
				 return true;
			       return false;
			    });
	  if (it3 != tmp->getModel().getSpells().end()){
	    std::cout << "Found Spell" << std::endl;
	    Client::getInstance()->spell( (**_wMan->getBattle())->getId(), **it3,
					  _currentTurn,
					  _selectedMob->getPlayerId());
	    _selectedMob = NULL;
	    _spellSpriteCase->setVisible(false);
	    _spellSprite->setVisible(false);
	    _selectedSpell = "";
	    (static_cast<QApplication *>(QApplication::instance()))->setOverrideCursor(QCursor(QPixmap("./Res/cursor.png"), 0, 0));
	  }
	}
    }
}

void			BattleView::rightButton(QMouseEvent *)
{
  _selectedMob = NULL;
  _selectedSpell = "";
  _spellSprite->setVisible(false);
  (static_cast<QApplication *>(QApplication::instance()))->setOverrideCursor(QCursor(QPixmap("./Res/cursor.png"), 0, 0));
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

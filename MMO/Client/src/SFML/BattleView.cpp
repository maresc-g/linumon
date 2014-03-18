//
// BattleView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 18:11:57 2014 cyril jourdain
// Last update Tue Mar 18 10:54:58 2014 cyril jourdain
//

#include		<stdexcept>
#include		<QMenu>
#include		"SFML/BattleView.hh"
#include		"Entities/Digitaliser.hh"
#include <QDebug>

BattleView::BattleView(SFMLView *v, WindowManager *w) :
  ContextView(v,w), _playerList(new std::list<MobSprite*>()),
  _enemyList(new std::list<MobSprite*>()), _playingMob(NULL), _selectedMob(NULL),
  _selectedSpell(""), _currentTurn(-1), _battleStarted(false)
{
  // (*_buttonMap)[Qt::NoButton] = &BattleView::noButton;
  // (*_buttonMap)[Qt::LeftButton] = &BattleView::leftButton;
  // (*_buttonMap)[Qt::RightButton] = &BattleView::rightButton;
}

BattleView::~BattleView()
{
}

void			BattleView::onInit()
{
  _spellUpdater = new BattleSpellUpdater(_sfmlView, _wMan);
  _buttonMap = new ButtonMap;
  _backgroundTexture = new sf::RenderTexture();
  _backgroundSprite = new sf::Sprite();
  _countDownSprite = new Sprite();
  (*_buttonMap)[Qt::NoButton] = &BattleView::noButton;
  (*_buttonMap)[Qt::LeftButton] = &BattleView::leftButton;
  (*_buttonMap)[Qt::RightButton] = &BattleView::rightButton;
  _selection = new Sprite();
  _spellSprite = new Sprite();
  _spellSpriteCase = new Sprite();
  _battleScreen = new Sprite();
  _selectedSpell = "";
  _currentTurn = -1;
  _battleResult = NULL;

  _backgroundTexture->create(BATTLE_SIZE * CASE_SIZE, BATTLE_SIZE*CASE_SIZE);
  loadBackgroundMap();
  loadBackgroundSprite();
  loadPlayerList();
  _playingMob = NULL;
  _sfmlView->getSpriteManager()->copySprite("selectedPlayer", *_selection);
  _sfmlView->getSpriteManager()->copySprite("Lance-Flamme", *_spellSprite);
  _sfmlView->getSpriteManager()->copySprite("translucentCase", *_spellSpriteCase);
  _sfmlView->getSpriteManager()->copySprite("battleScreen", *_battleScreen);
  _sfmlView->getSpriteManager()->copySprite("countDown", *_countDownSprite);
  _selection->play("default_down");
  // _spellSprite->play("mouse");
  _spellSpriteCase->play("default");
  _spellSpriteCase->setVisible(false);
  (*_spellSprite)["mouse"]->setFrameLength(120000);
  (*_selection)["default_down"]->setFrameLength(45000);
  (*_battleScreen)["default"]->setFrameLength(1500000);
  (*_battleScreen)["default"]->setLoopPlay(false);
  (*_countDownSprite)["default"]->setFrameLength(1000000);
  (*_countDownSprite)["default"]->setLoopPlay(false);
  _battleScreen->play("default");
  _countDownSprite->setOrigin(64,64);
  _countDownSprite->scale(2,2);
  _countDownSprite->setPosition((BATTLE_SIZE * CASE_SIZE / 2), (BATTLE_SIZE * CASE_SIZE / 2));
  // _battleScreen->scale(WIN_W / _battleScreen->getCurrentBound()->width,
  // 		       WIN_H / _battleScreen->getCurrentBound()->height);
  _battleScreen->scale(static_cast<float>(WIN_W) / static_cast<float>(_battleScreen->getCurrentBound()->width),
		       static_cast<float>(WIN_H) / static_cast<float>(_battleScreen->getCurrentBound()->height));
  //_battleStarted = true;
  _battleStarted = false;
}
void			BattleView::onUpdate()
{
  // if (_battleResult && _battleResult->getPlayCount() > 0)
  //   {
  //     _battleResult->update(*_sfmlView->getMainClock());
  //     return;
  //   }
  if (_battleStarted){
    if (_countDownSprite->isAnimFinished()){
      // std::cout << "Updating battle" << std::endl;
      if (**(**(_wMan)->getBattle())->getSwitch())
	{
	  loadPlayerList();
	  _currentTurn = -1;
	  *(**(_wMan)->getBattle())->getSwitch() = false;
	  _playingMob = NULL;
	  setLifeVisibility(true);
	}
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
    else{
      _countDownSprite->update(*_sfmlView->getMainClock());
    }
  }
  else
    {
      _battleScreen->update(*_sfmlView->getMainClock());
      std::cout << "update battle screen" << std::endl;
    }
}

void			BattleView::onKeyEvent(QKeyEvent *)
{
}

void			BattleView::onMouseEvent(QMouseEvent *event)
{
  try{
    (this->*(_buttonMap->at(event->button())))(event);
  } catch (std::out_of_range const &e){
    std::cerr << "BattleView::onMouseEvent : Warning - Button not handled" << std::endl; 
    return;
  }
}

void			BattleView::resetView()
{
}

void			BattleView::drawView()
{
  if (_battleResult && _battleResult->getPlayCount() > 0)
    _sfmlView->draw(*_battleResult);
  if (_battleStarted){
    _backgroundSprite->setTexture(_backgroundTexture->getTexture());
    _sfmlView->draw(*_backgroundSprite);
    _sfmlView->draw(*_spellSpriteCase);
    for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
      {
	(*it)->resetHUDPos();
	_sfmlView->draw(*(*it));
	(*it)->update(*_sfmlView->getMainClock());
	if (_spellUpdater->endTurn())
	  (*it)->upHealthBar();
      }
    for (auto it = _enemyList->begin(); it != _enemyList->end(); ++it)
      {
	(*it)->resetHUDPos();
	_sfmlView->draw(*(*it));
	(*it)->update(*_sfmlView->getMainClock());
	if (_spellUpdater->endTurn())
	  (*it)->upHealthBar();
      }
    _sfmlView->draw(*_selection);
    _sfmlView->draw(*_spellSprite);
    _spellUpdater->draw();
    _sfmlView->draw(*_countDownSprite);
  }
  else{
      _sfmlView->draw(*_battleScreen);
  }
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
  qDebug() << "View centered";
}

void			BattleView::spellClick(std::string const &spell)
{
  if (playerTurn()) {
      (static_cast<QApplication *>(QApplication::instance()))->setOverrideCursor(QCursor(Qt::BlankCursor));
    if (!_sfmlView->getSpriteManager()->copySprite(spell, *_spellSprite)) {
      _sfmlView->getSpriteManager()->copySprite("Surf", *_spellSprite);
    }
    _spellSprite->setVisible(true);
    _spellSprite->play("mouse");
    _selectedSpell = spell;
  }
}

std::list<MobSprite*>	*BattleView::getPlayerList() const {return _playerList; }
std::list<MobSprite*>	*BattleView::getEnemyList() const {return _enemyList; }
BattleMob		*BattleView::findMobById(unsigned int id) const
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
    return new BattleMob(PLAYER, *it);
  if (it != _enemyList->end())
    return new BattleMob(ENEMY, *it);
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
  // _playingMob = NULL;
  // _selectedMob = NULL;
  // _spellSprite = NULL;
  // _spellSpriteCase = NULL;
  _selectedSpell = "";
  delete _spellUpdater;
  delete _backgroundSprite;
  delete _backgroundTexture;
  delete _battleResult;
  _backgroundSprite = NULL;
  _backgroundTexture = NULL;
  _spellUpdater = NULL;
  _currentTurn = -1;
  _battleStarted = false;
}

bool			BattleView::isBattleEnded()
{
  if (_battleStarted)
    {
      if (_spellUpdater->endTurn())
	return true;
    }
  return false;
}

void			BattleView::battleStart()
{
  _battleStarted = true;
  _countDownSprite->play("default");
}

bool			BattleView::canStartBattle()
{
  if (_battleScreen->isAnimFinished())
    return true;
  return false;
}

void			BattleView::printBattleResult()
{
  _battleResult = new Sprite();
  _sfmlView->getSpriteManager()->copySprite("BattleResult", *_battleResult);
  _battleResult->play("win");
}

void			BattleView::loadPlayerList()
{
  std::list<Mob*> const 	mobs = (**_wMan->getBattle())->getMobs();
  std::list<Mob*>	enemyMobs = (**_wMan->getBattle())->getEnemy().getDigitaliser().getBattleMobs();
  int			posY = 2 * CASE_SIZE;
  int			limit = 0;
  MobSprite		*tmp;

  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    delete *it;
  for (auto it = _enemyList->begin(); it != _enemyList->end(); it++)
    delete *it;
  _playerList->clear();
  _enemyList->clear();

  for (auto it = mobs.begin(); it != mobs.end() && limit < 3; ++it)
    {
      tmp = new MobSprite((static_cast<Mob*>(*it))->getName(),
			  _sfmlView->getFont(), _wMan);
      _sfmlView->getSpriteManager()->copySprite("Nyan", *tmp);
      tmp->play("default_up");
      tmp->generateOffset();
      tmp->setPosition(posY, ((BATTLE_SIZE- 2) * CASE_SIZE) - tmp->getCurrentBound()->height / 2 + 4);
      tmp->setPos(posY / CASE_SIZE, BATTLE_SIZE - 2);
      tmp->setPlayerId((*it)->getId(), false);
      tmp->setText(std::string((*it)->getName() + " [" + std::to_string((*it)->getLevel()) + "]"));
      tmp->setHUDInfo(*(static_cast<Mob*>(*it)));
      tmp->setInfoVisibility(false);
      tmp->initHealthBar(*(static_cast<Mob*>(*it)));
      _playerList->push_back(tmp);
      posY += 3*CASE_SIZE;
      limit++;
      qDebug() << "Adding player with id : " << (*it)->getId();
    }
  posY = 2*CASE_SIZE;
  for (auto it = enemyMobs.begin(); it != enemyMobs.end(); ++it)
    {
      tmp = new MobSprite((static_cast<Mob*>(*it))->getName(),
			  _sfmlView->getFont(), _wMan);
      _sfmlView->getSpriteManager()->copySprite("Dragoball", *tmp);
      tmp->play("default_down");
      tmp->generateOffset();
      tmp->setPosition(posY, ((2) * CASE_SIZE) - tmp->getCurrentBound()->height / 2 + 4);
      tmp->setPos(posY / CASE_SIZE, 2);
      tmp->setPlayerId((*it)->getId(), false);
      tmp->setText(std::string((*it)->getName() + " [" + std::to_string((*it)->getLevel()) + "]"));
      tmp->initHealthBar(*(static_cast<Mob*>(*it)));
      _enemyList->push_back(tmp);
      posY += 3*CASE_SIZE;
    }  
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
			       if (val->getName() == _selectedSpell)
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

void			BattleView::rightButton(QMouseEvent *event)
{
  if (_selectedMob) {
    BattleMob *mob = findMobById(_selectedMob->getPlayerId());
    QMenu menu;

    if (mob->type == PLAYER)
      {
	menu.addAction("Switch");
      }
    else if (mob->type == ENEMY)
      menu.addAction("Capture");
    else
      return;
    QAction *action = menu.exec(QPoint(event->x(), event->y()));

    if (action)
      {
	if (action->text().toStdString() == "Switch")
	  switchMobs(_selectedMob->getPlayerId());
      }
    else
      {
	std::cout << "not so lol" << std::endl;
      }
  }
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
  if (!found)
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

void				BattleView::switchMobs(unsigned int mobId)
{
  std::cout << "switch mobs here" << std::endl;
  SwitchMobView	*v = new SwitchMobView(_sfmlView, &(**_wMan->getMainPlayer())->getDigitaliser().getBattleMobs(), _wMan);
  int change = v->exec();
  Client::getInstance()->sendSwitch((**_wMan->getBattle())->getId(), mobId, change);
  qDebug() << "change mob " << mobId << " with " << change;
}

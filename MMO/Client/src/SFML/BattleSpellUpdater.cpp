//
// BattleSpellUpdater.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar  8 20:48:56 2014 cyril jourdain
// Last update Wed Mar 26 10:14:56 2014 cyril jourdain
//

#include			"SFML/BattleSpellUpdater.hh"
#include			"SFML/BattleView.hh"
#include <QDebug>

BattleSpellUpdater::BattleSpellUpdater(SFMLView *sfml, WindowManager *w) :
  _sfmlView(sfml), _wMan(w), _currentSpell(new Sprite()), _previousTarget(NULL)
{
}

BattleSpellUpdater::~BattleSpellUpdater()
{
}

void				BattleSpellUpdater::update(BattleView *battle)
{
  SpellContainer		*tmp = NULL;
  // BattleMob			*mob = NULL;

  if (_currentSpell->isAnimFinished() && ((_previousTarget && _previousTarget->mob && _previousTarget->mob->isHealthBarUpdated()) || !_previousTarget))
    {      
      if ((tmp = (**_wMan->getBattle())->getSpell()))
	{
	  std::cout << tmp->getSpell().getName() << std::endl;
	  if (!_sfmlView->getSpriteManager()->copySprite(tmp->getSpell().getName(), *_currentSpell))
	    !_sfmlView->getSpriteManager()->copySprite("Fatal-Foudre", *_currentSpell);
	  _previousTarget = battle->findMobById(tmp->getTarget());
	  if (!_previousTarget || _previousTarget->type == NOMOB)
	    return;
	  // mob->mob->upHealthBar();
	  _currentSpell->setPosition(_previousTarget->mob->getPos()->x * CASE_SIZE,
				     _previousTarget->mob->getPos()->y * CASE_SIZE - CASE_SIZE / 2);
	  (*_currentSpell)["onEnemy"]->setLoopPlay(false);
	  (*_currentSpell)["onEnemy"]->setFrameLength(80000);
	  _currentSpell->play("onEnemy");
	  //_currentSpell->update(*_sfmlView->getMainClock());
	  delete tmp;
	  // delete mob;
	}
    }
  else
    _currentSpell->update(*_sfmlView->getMainClock());
}

void				BattleSpellUpdater::draw()
{
  sf::Vector2f			tmp;

  if (_currentSpell->getLastPlayed() != "")
    {
      tmp = _currentSpell->getPosition();
      _currentSpell->setPosition(tmp.x + _currentSpell->getCurrentOffset()->x,
				 tmp.y + _currentSpell->getCurrentOffset()->y);
      _sfmlView->draw(*_currentSpell);
      _currentSpell->setPosition(tmp);
    }
}


bool				BattleSpellUpdater::endTurn()
{
  if (_currentSpell->isAnimFinished())
    return true;
  return false;
}

BattleMob			*BattleSpellUpdater::getPreviousTarget() const
{
  return _previousTarget;
}

void				BattleSpellUpdater::unsetPreviousTarget()
{
  _previousTarget = NULL;
}

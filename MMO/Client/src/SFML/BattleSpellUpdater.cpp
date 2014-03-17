//
// BattleSpellUpdater.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar  8 20:48:56 2014 cyril jourdain
// Last update Sun Mar 16 21:47:45 2014 cyril jourdain
//

#include			"SFML/BattleSpellUpdater.hh"
#include			"SFML/BattleView.hh"
#include <QDebug>

BattleSpellUpdater::BattleSpellUpdater(SFMLView *sfml, WindowManager *w) :
  _sfmlView(sfml), _wMan(w), _currentSpell(new Sprite())
{
}

BattleSpellUpdater::~BattleSpellUpdater()
{
}

void				BattleSpellUpdater::update(BattleView *battle)
{
  SpellContainer		*tmp = NULL;
  BattleMob			*mob = NULL;

  if (_currentSpell->isAnimFinished())
    {      
      if ((tmp = (**_wMan->getBattle())->getSpell()))
	{
	  qDebug() << "Something found";
	  _sfmlView->getSpriteManager()->copySprite("Fatal-Foudre", *_currentSpell);
	  mob = battle->findMobById(tmp->getTarget());
	  if (!mob || mob->type == NOMOB)
	    return;
	  // mob->mob->upHealthBar();
	  _currentSpell->setPosition(mob->mob->getPos()->x * CASE_SIZE,
				     mob->mob->getPos()->y * CASE_SIZE - CASE_SIZE / 2);
	  (*_currentSpell)["onEnemy"]->setLoopPlay(false);
	  (*_currentSpell)["onEnemy"]->setFrameLength(80000);
	  _currentSpell->play("onEnemy");
	  //_currentSpell->update(*_sfmlView->getMainClock());
	  delete tmp;
	  delete mob;
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


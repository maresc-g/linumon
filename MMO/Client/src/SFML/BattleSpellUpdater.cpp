//
// BattleSpellUpdater.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar  8 20:48:56 2014 cyril jourdain
// Last update Tue Mar 11 16:13:47 2014 cyril jourdain
//

#include			"SFML/BattleSpellUpdater.hh"
#include			"SFML/BattleView.hh"

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
  MobSprite			*mob = NULL;

  if (_currentSpell->isAnimFinished())
    {
      if ((tmp = (**_wMan->getBattle())->getSpell()))
	{
	  std::cout << "Playing SPELL" << std::endl;
	  _sfmlView->getSpriteManager()->copySprite("Danse-Fleur", *_currentSpell);
	  mob = battle->findMobById(tmp->getTarget());
	  if (!mob)
	    return;
	  mob->upHealthBar();
	  _currentSpell->setPosition(mob->getPos()->x * CASE_SIZE,
				     mob->getPos()->y * CASE_SIZE - CASE_SIZE / 2);
	  (*_currentSpell)["onEnemy"]->setLoopPlay(false);
	  (*_currentSpell)["onEnemy"]->setFrameLength(80000);
	  _currentSpell->play("onEnemy");
	  _currentSpell->update(*_sfmlView->getMainClock());
	  delete tmp;
	}
    }
  _currentSpell->update(*_sfmlView->getMainClock());
}

void				BattleSpellUpdater::draw()
{
  if (_currentSpell->getLastPlayed() != "")
    _sfmlView->draw(*_currentSpell);
}


bool				BattleSpellUpdater::endTurn()
{
  if (_currentSpell->isAnimFinished())
    return true;
  return false;
}


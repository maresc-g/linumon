//
// BattleSpellUpdater.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar  8 20:48:56 2014 cyril jourdain
// Last update Sun Mar  9 17:07:37 2014 guillaume marescaux
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

  if (_currentSpell->getLastPlayed() == "")
    {
      if ((tmp = (**_wMan->getBattle())->getSpell()))
	{
	  std::cout << "SPELL NOT NULL" << std::endl;
	  _sfmlView->getSpriteManager()->copySprite(tmp->getSpell().getName(), *_currentSpell);
	  mob = battle->findMobById(tmp->getTarget());
	  if (!mob)
	    return;
	  std::cout << "MOB NOT NULL" << std::endl;
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
  else {
    _currentSpell->update(*_sfmlView->getMainClock());
  }
}

void				BattleSpellUpdater::draw()
{
  if (_currentSpell->getLastPlayed() != "")
    _sfmlView->draw(*_currentSpell);
}

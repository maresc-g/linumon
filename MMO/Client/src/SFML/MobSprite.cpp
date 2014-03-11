//
// MobSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Mar  7 14:46:04 2014 cyril jourdain
// Last update Tue Mar 11 18:12:32 2014 guillaume marescaux
//

#include		"SFML/MobSprite.hh"
#include		"Client.hh"
#include		"SFML/BattleView.hh"

# define			GREEN "#33C71F"
# define			ORANGE "#E77E18"
# define			RED "#E72518"

MobSprite::MobSprite(sf::String const &name, sf::Font * font, WindowManager *wMan) :
  PlayerSprite(name, font), _wMan(wMan), _spellBar(new SpellBarView(wMan->getSFMLView(), wMan)), _hud(new HUDView(wMan->getSFMLView(), wMan)),
  _pb(new QProgressBar(wMan->getSFMLView()))
{
  _hud->hide();
  _spellBar->hide();
  _pb->hide();
  _pb->resize(100,20);
  _isVisible = false;
  _pb->setFormat("%v/%m");
  _pb->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

MobSprite::~MobSprite()
{
  delete _spellBar;
  delete _hud;
  delete _pb;
}

void			MobSprite::setHUDInfo(Mob const &mob)
{
  _spellBar->setInfos(mob.getModel().getSpells());
  _hud->setInfos(&mob);
  _spellBar->move(WIN_W / 2 - _spellBar->size().width() / 2, WIN_H - _spellBar->size().height());
  _hud->move(WIN_W / 2 - _hud->size().width() / 2, 0);
}

void			MobSprite::initHealthBar(Mob const &mob)
{
  _mob = &mob;
  // std::cout << "MOB NAME = " << mob.getName() << " HP MAX = " << mob.getStat("HP") << " HP CUR = " << mob.getTmpStat("HP") << std::endl;
  upHealthBar();
}

void			MobSprite::upHealthBar()
{
  double		current = _mob->getCurrentStat("HP");
  unsigned int		max = _mob->getMaxStat("HP");
  // std::cout << "CURRENT = " << current << std::endl;
  // std::cout << "MAX = " << max << std::endl;
  // std::cout << "CUR / MAX = " << (double)(current / max) << std::endl;
  // std::cout << "CUR / MAX in % = " << (double)(current / max) * 100 << std::endl;
  _pb->setMaximum(max);
  _pb->setValue(current);
  if (max)
    {
      if ((double)(current / max) * 100 <= 20)
  	_pb->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(RED) + "; }").c_str());
      else if ((double)(current / max) * 100 <= 50)
  	_pb->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(ORANGE) + "; }").c_str());
      else
  	_pb->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(GREEN) + "; }").c_str());
    }
  else
    _pb->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(GREEN) + "; }").c_str());
  _pb->show();
}

void			MobSprite::setInfoVisibility(bool v)
{
  _hud->setVisible(v);
  _spellBar->setVisible(v);
}

void			MobSprite::resetHUDPos()
{
  if (_pb && _isVisible){
    sf::Vector2i p = _wMan->getSFMLView()->mapCoordsToPixel(getPosition());
    _pb->move(p.x, p.y - (getCurrentBound()->height / 2 + 5));
  }
}

void			MobSprite::setLifeVisibility(bool v)
{
  _pb->setVisible(v);
  _isVisible = v;
}

void			MobSprite::onClick()
{
  // std::cout << "other player clicked" << std::endl;
}

void			MobSprite::setPosition(int x, int y)
{
  sf::Transformable::setPosition(x, y);
  _pb->move(x, y - 20);
}

void			MobSprite::update(sf::Clock &clock)
{
  upHealthBar();
  Sprite::update(clock);
}

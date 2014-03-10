//
// MobSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Mar  7 14:46:04 2014 cyril jourdain
// Last update Fri Mar  7 16:39:26 2014 cyril jourdain
//

#include		"SFML/MobSprite.hh"
#include		"Client.hh"

MobSprite::MobSprite(sf::String const &name, sf::Font * font, WindowManager *wMan) :
  PlayerSprite(name, font), _spellBar(new SpellBarView(wMan->getSFMLView(), wMan)), _hud(new HUDView(wMan->getSFMLView(), wMan))
{
  _hud->hide();
  _spellBar->hide();
}

MobSprite::~MobSprite()
{
}

void			MobSprite::setHUDInfo(Mob const &mob)
{
  _spellBar->setInfos(mob.getModel().getSpells());
  _hud->setInfos(&mob);
  _spellBar->move(WIN_W / 2 - _spellBar->size().width() / 2, WIN_H - _spellBar->size().height());
  _hud->move(WIN_W / 2 - _hud->size().width() / 2, 0);
}

void			MobSprite::setInfoVisibility(bool v)
{
  std::cout << "lol" << std::endl;
  _hud->setVisible(v);
  _spellBar->setVisible(v);
}

void			MobSprite::onClick()
{
  std::cout << "other player clicked" << std::endl;
}


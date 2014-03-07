//
// BattleView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 17:57:46 2014 cyril jourdain
// Last update Fri Mar  7 13:20:45 2014 cyril jourdain
//

#ifndef 		__BATTLEVIEW_HH__
# define 		__BATTLEVIEW_HH__

# define			BATTLE_SIZE 11

# include			"SFML/ContextView.hh"


class				BattleView : public ContextView
{
private:
  std::list<OPlayerSprite*>	*_playerList;
  std::list<OPlayerSprite*>	*_enemyList;
  OPlayerSprite			*_playingMob;
  OPlayerSprite			*_selectedMob;
  Sprite			*_selection;
  Sprite			*_spellSprite;
  Sprite			*_spellSpriteCase;

public:
  BattleView(SFMLView *, WindowManager *);
  virtual ~BattleView();

public:
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onKeyEvent(sf::Event const &);
  virtual void			onMouseEvent(QMouseEvent *event);
  virtual void			resetView();
  virtual void			drawView();
  virtual void			loadBackgroundMap();
  virtual void			resetPOV();
  virtual void			centerView();
};

#endif

//
// BattleView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 17:57:46 2014 cyril jourdain
// Last update Fri Mar  7 22:13:51 2014 cyril jourdain
//

#ifndef 		__BATTLEVIEW_HH__
# define 		__BATTLEVIEW_HH__

# define			BATTLE_SIZE 11

# include			"SFML/ContextView.hh"
# include			"SFML/MobSprite.hh"


class				BattleView : public ContextView
{
private:
  typedef std::map<Qt::MouseButton, void (BattleView::*)(QMouseEvent *)> ButtonMap;

private:
  ButtonMap			*_buttonMap;
  std::list<MobSprite*>		*_playerList;
  std::list<MobSprite*>		*_enemyList;
  MobSprite			*_playingMob;
  MobSprite			*_selectedMob;
  Sprite			*_selection;
  Sprite			*_spellSprite;
  Sprite			*_spellSpriteCase;
  std::string			_selectedSpell;

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
  void				spellClick(std::string const &);

private:
  bool				playerTurn() const;
  void				leftButton(QMouseEvent *);
  void				rightButton(QMouseEvent *);
  void				noButton(QMouseEvent *);
};

#endif

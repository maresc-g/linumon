//
// WorldView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 17 15:32:06 2014 cyril jourdain
// Last update Fri Mar 14 12:44:52 2014 cyril jourdain
//

#ifndef				__WORLDVIEW_HH__
# define	 		__WORLDVIEW_HH__

#include			"SFML/ContextView.hh"
#include			"SFML/PlayerSprite.hh"
#include			"SFML/OPlayerSprite.hh"
#include			"SFML/RessourceSprite.hh"
#include			"Qt/Views/PlayerClickView.hh"

class				WorldView : public ContextView
{

private:
  typedef std::map<Qt::Key, void (WorldView::*)()> KeyMap;

private:
  PlayerSprite			*_mainPerso;
  std::vector<OPlayerSprite *>	*_playerList;
  std::list<RessourceSprite*>	*_entities;
  std::list<RessourceSprite*>	*_topLayer;
  KeyMap			*_keyMap;
  Qt::Key			_pressedKey;

private: /* Child views */
  PlayerClickView		*_clickView;

public:
  WorldView(SFMLView *, WindowManager *);
  virtual ~WorldView();

public:
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onKeyEvent(QKeyEvent *);
  virtual void			onMouseEvent(QMouseEvent *event);
  virtual void			resetView();
  virtual void			drawView();
  virtual void			resetPOV();

private:
  void				loadPlayerList();
  void				loadEntities();
  void				keyUp();
  void				keyDown();
  void				keyLeft();
  void				keyRight();
  void				keyI();
  void				keyS();
  void				keyJ();
  void				keyD();
  void				keyG();
  void				keyEscape();
  void				keyReturn();
  void				keyControl();
};

#endif

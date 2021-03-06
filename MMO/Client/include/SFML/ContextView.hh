//
// ContextView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Mar  2 23:49:12 2014 cyril jourdain
// Last update Fri Mar 14 11:37:17 2014 cyril jourdain
//

#ifndef 		__CONTEXTVIEW_HH__
# define 		__CONTEXTVIEW_HH__

#include		"SFML/SFMLView.hpp"

class			SFMLView;

class			ContextView
{
protected:
  typedef std::map<int, std::map<int, Sprite *>> SpriteMap;
  SFMLView		*_sfmlView;
  WindowManager		*_wMan;
  SpriteMap		*_spriteMap;
  sf::RenderTexture	*_backgroundTexture;
  sf::Sprite		*_backgroundSprite;

public:
  ContextView(SFMLView *v, WindowManager *w);
  virtual ~ContextView();

public:
  virtual void		onInit() = 0;
  virtual void		onUpdate() = 0;
  virtual void		onKeyEvent(QKeyEvent *) = 0;
  virtual void		onMouseEvent(QMouseEvent *) = 0;
  virtual void		resetView() = 0;
  virtual void		drawView() = 0;
  virtual void		loadBackgroundMap();
  virtual void		loadBackgroundSprite();
  virtual void		resetPOV();
  virtual void		centerView();
};

#endif

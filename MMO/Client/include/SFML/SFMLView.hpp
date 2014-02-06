//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Thu Feb  6 13:20:54 2014 cyril jourdain
//

#ifndef 		__SFMLVIEW_HPP__
# define 		__SFMLVIEW_HPP__

#include		"Qt/QSFMLWidget.hpp"
#include		"Qt/WindowManager.hh"

#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

class WindowManager;

class			SFMLView : public QSFMLWidget
{
private:
  WindowManager		*_wMan;
  SpriteManager		*_sMan;
  Sprite		*_mainPerso;
  sf::Clock		*_clock;
  sf::View		*_view;
  sf::Sprite		*_spriteTest;
  sf::Texture		*_textureTest;
  /* Here the attributes of the class */

  sf::Vector2f		_pos;
  sf::Vector2f		_deltaPos;

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

private :
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onResize(QResizeEvent *);
  void				drawView();
  void				checkKeys();
  void				moveMainPerso(float const elapsedTime);
};

#endif

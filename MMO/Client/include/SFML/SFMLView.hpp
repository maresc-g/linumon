//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Tue Feb  4 12:32:53 2014 cyril jourdain
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
  Sprite		*_sprite;
  sf::Texture		*_texture;
  sf::Clock		*_clock;
  /* Here the attributes of the class */

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

private :
  virtual void			onInit();
  virtual void			onUpdate();
};

#endif

//
// Window.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 20 15:40:22 2014 cyril jourdain
// Last update Fri Mar 21 11:20:10 2014 cyril jourdain
//

#ifndef 		__WINDOW_HH__
# define 		__WINDOW_HH__

#include		<SFML/System.hpp>
#include		<SFML/Graphics.hpp>
#include		<QMouseEvent>
#include		<QKeyEvent>
#include		"SFML/SFMLView.hpp"

class			Window
{
protected:
  SFMLView		*_sfmlView;
  bool			_modal;

public:
  Window(SFMLView *v) : _sfmlView(v), _modal(false) {};
  virtual ~Window() {};

public:
  virtual void		draw() const = 0;
  virtual void		update(sf::Clock &) = 0;
  virtual void		onKeyEvent(QKeyEvent *) = 0;
  virtual void		onMouseEvent(QMouseEvent *event) = 0;
  void			setModal(bool v) {_modal = v; };
  bool			isModal() const {return _modal; };
};

#endif

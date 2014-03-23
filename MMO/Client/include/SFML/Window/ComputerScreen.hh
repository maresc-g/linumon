//
// ComputerScreen.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 20 15:44:41 2014 cyril jourdain
// Last update Sat Mar 22 22:24:56 2014 cyril jourdain
//

#ifndef 		__COMPUTERSCREEN_HH__
# define 		__COMPUTERSCREEN_HH__

# include		"SFML/Window.hh"
# include		"SFML/Sprite/Sprite.hh"

#define TEXT "$> .... INITIALIZATION ....\n$> .... OK ....\n$> .... PREPARING HEALER .... \n$> .... OK .... \n$> \n$> \n$> Do you want to heal all your monsters ?"

class			ComputerScreen : public Window
{
private:
  Sprite		*_background;
  Sprite		*_arrow;
  std::string		_text;
  sf::Text		*_textDraw;
  sf::Text		*_yes;
  sf::Text		*_no;
  unsigned int		_pos;
  sf::Clock		_clock;
  sf::Text		*_selection;

public:
  ComputerScreen(SFMLView *);
  ComputerScreen(SFMLView *, std::string const &text);
  virtual ~ComputerScreen();

public:
  virtual void		draw() const;
  virtual void		update(sf::Clock &);
  virtual void		onKeyEvent(QKeyEvent *);
  virtual void		onMouseEvent(QMouseEvent *event);

private:
  void			initText(sf::Text *, std::string const &);
};

#endif

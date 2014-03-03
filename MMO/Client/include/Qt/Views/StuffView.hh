//
// StuffView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:08:03 2014 guillaume marescaux
// Last update Thu Feb 27 15:55:45 2014 guillaume marescaux
//

#ifndef 		__STUFFVIEW_HH__
# define 		__STUFFVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_stuffview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/ItemView.hh"
#include		"Entities/Player.hh"

class			WindowManager;

class			StuffView : public QWidget
{
  Q_OBJECT

public:
  StuffView(QWidget *, WindowManager *wman = NULL);
  virtual ~StuffView();

private:
  Ui::stuffview		ui;
  WindowManager		*_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);

public:
  void			initStuff(Player const &player);
  void			initStuff(Mob const &mob);
};

#endif

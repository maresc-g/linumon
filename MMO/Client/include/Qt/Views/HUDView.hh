//
// HUDView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar  6 13:09:22 2014 guillaume marescaux
// Last update Thu Mar  6 13:27:01 2014 guillaume marescaux
//

#ifndef 		__HUDVIEW_HH__
# define 		__HUDVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_hudview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/MobView.hh"

class			HUDView : public QWidget
{
  Q_OBJECT

public:

  HUDView(QWidget *, WindowManager *wMan);
  virtual ~HUDView();

private:

  Ui::hudview		ui;
  WindowManager		*_wMan;
  MobView		*_mobView;

private:

  virtual void		paintEvent(QPaintEvent *);

public:

  void			setInfos(Mob const *mob);
};

#endif

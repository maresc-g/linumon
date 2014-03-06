//
// TinyHUDView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar  6 14:20:36 2014 guillaume marescaux
// Last update Thu Mar  6 14:20:56 2014 guillaume marescaux
//

#ifndef 		__TINYHUDVIEW_HH__
# define 		__TINYHUDVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_hudview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/MobView.hh"

class			TinyHUDView : public QWidget
{
  Q_OBJECT

public:

  TinyHUDView(QWidget *, WindowManager *wMan);
  virtual ~TinyHUDView();

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

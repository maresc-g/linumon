//
// MenuView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb 17 13:28:07 2014 guillaume marescaux
// Last update Tue Feb 18 15:21:28 2014 guillaume marescaux
//

#ifndef 		__MENUVIEW_HH__
# define 		__MENUVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_menuview.h"
#include		"Qt/WindowManager.hh"

class			MenuView : public QWidget
{
  Q_OBJECT

public:

  MenuView(QWidget *, WindowManager *wMan);
  virtual ~MenuView();

private:

  Ui::menuview		ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_bSwitch_clicked();
  void			on_bLogout_clicked();
  void			on_bQuit_clicked();
  void			on_bReturn_clicked();
};

#endif

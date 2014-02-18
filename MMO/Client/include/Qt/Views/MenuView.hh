//
// MenuView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb 17 13:28:07 2014 guillaume marescaux
// Last update Tue Feb 18 11:34:33 2014 guillaume marescaux
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

  void			bSwitch_clicked();
  void			bLogout_clicked();
  void			bQuit_clicked();
  void			bReturn_clicked();
};

#endif

//
// loginView.hh for  in /home/jourda_c/Documents/PFA/Sources/include/qtclasses
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Oct 18 10:58:49 2013 cyril jourdain
// Last update Thu Feb 27 15:55:33 2014 guillaume marescaux
//

#ifndef 		__LOGINVIEW_HH__
# define 		__LOGINVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_loginview.h"
#include		"Qt/WindowManager.hh"

class			WindowManager;

class			LoginView : public QWidget
{
  Q_OBJECT

public:
  LoginView(QWidget *, WindowManager *wman = NULL);
  virtual ~LoginView();

private:
  Ui::loginView	ui;
  WindowManager		*_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);

public slots:
  void			on_bConnect_clicked();

};

#endif

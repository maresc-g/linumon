//
// loginView.hh for  in /home/jourda_c/Documents/PFA/Sources/include/qtclasses
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Oct 18 10:58:49 2013 cyril jourdain
// Last update Tue Dec 17 12:58:48 2013 cyril jourdain
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
  WindowManager		*_wMan;

public:
  LoginView(QWidget *, WindowManager *wman = NULL);
  ~LoginView();

private:
  Ui::loginView	ui;

private:
  virtual void		paintEvent(QPaintEvent *);

public slots:
  void			on_bConnect_clicked();

};

#endif

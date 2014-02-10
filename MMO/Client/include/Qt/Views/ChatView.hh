//
// ChatView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Feb  6 14:47:23 2014 cyril jourdain
// Last update Mon Feb 10 13:15:45 2014 cyril jourdain
//

#ifndef 		__CHATVIEW_HH__
# define 		__CHATVIEW_HH__

#include		<QWidget>
#include		<Qt/qpainter.h>
#include		"ui_chatview.h"
#include		"Qt/WindowManager.hh"

class WindowManager;

class			ChatView : public QWidget
{
  Q_OBJECT

public:
  ChatView(QWidget *, WindowManager *);
  virtual ~ChatView();

private:
  Ui::ChatView	ui;
  WindowManager *_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);

};

#endif

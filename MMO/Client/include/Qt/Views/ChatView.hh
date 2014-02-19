//
// ChatView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Feb  6 14:47:23 2014 cyril jourdain
// Last update Wed Feb 19 14:43:01 2014 cyril jourdain
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

private:
  Ui::ChatView	ui;
  WindowManager *_wMan;
  bool		_focused;
  
public:
  ChatView(QWidget *, WindowManager *);
  virtual ~ChatView();

private:

public:  
  bool			getFocused() const;
  void			setFocused(bool);
  void			submitText();
  void			update();


private:
  virtual void		paintEvent(QPaintEvent *);
};

#endif

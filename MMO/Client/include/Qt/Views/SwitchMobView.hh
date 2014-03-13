//
// SwitchMobView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 13 14:42:17 2014 cyril jourdain
// Last update Thu Mar 13 15:46:58 2014 cyril jourdain
//

#ifndef 		__SWITCHMOBVIEW_HH__
# define 		__SWITCHMOBVIEW_HH__

#include		<QWidget>
#include		<QScrollArea>
#include		<QFrame>
#include		"Entities/Digitaliser.hh"
#include		"ui_switchmobview.h"

class			SwitchMobView : public QDialog
{
  Q_OBJECT

private:
  Ui::SwitchMobView	ui;
  QScrollArea		*_scrollArea;
  QFrame		*_frame;

public:
  SwitchMobView(QWidget *, Digitaliser const &);
  virtual ~SwitchMobView();

private:
  virtual void		paintEvent(QPaintEvent *);
  virtual void		accept();
};

#endif

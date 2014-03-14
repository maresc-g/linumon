//
// SplitStackView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:56:36 2014 guillaume marescaux
// Last update Fri Mar 14 14:40:36 2014 guillaume marescaux
//

#ifndef 		__SPLITSTACKVIEW_HH__
# define 		__SPLITSTACKVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_splitstackview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/StackView.hh"
#include		"ParentInfos.hh"

class			SplitStackView : public QWidget
{
  Q_OBJECT

public:

  SplitStackView(QWidget *, WindowManager *wMan);
  virtual ~SplitStackView();

private:

  Ui::splitstackview	ui;
  WindowManager		*_wMan;
  StackView		*_source;
  StackView		*_dest;

private:

  virtual void		paintEvent(QPaintEvent *);
  ParentInfos		*getNameFirstParent(QWidget *parent);

private slots:

  void			on_b_accept_clicked();
  void			on_b_cancel_clicked();

public:

  void			setInfos(StackView *source, StackView *dest);
};

#endif

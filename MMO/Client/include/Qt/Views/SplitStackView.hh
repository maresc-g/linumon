//
// SplitStackView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:56:36 2014 guillaume marescaux
// Last update Wed Mar 12 14:09:07 2014 guillaume marescaux
//

#ifndef 		__SPLITSTACKVIEW_HH__
# define 		__SPLITSTACKVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_splitstackview.h"
#include		"Qt/WindowManager.hh"

class			SplitStackView : public QWidget
{
  Q_OBJECT

public:

  SplitStackView(QWidget *, WindowManager *wMan);
  virtual ~SplitStackView();

private:

  Ui::splitstackview	ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_accept_clicked();
  void			on_b_cancel_clicked();
};

#endif

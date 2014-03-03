//
// DigitaliserView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:26:29 2014 guillaume marescaux
// Last update Fri Feb 28 15:12:59 2014 guillaume marescaux
//

#ifndef 		__DIGITALISERVIEW_HH__
# define 		__DIGITALISERVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		<QScrollArea>
#include		<QFrame>
#include		"ui_digitaliserview.h"
#include		"Qt/WindowManager.hh"

class			DigitaliserView : public QWidget
{
  Q_OBJECT

private:

  WindowManager		*_wMan;
  QScrollArea		*_scrollArea;
  QFrame		*_frame;
  Ui::digitaliserview	ui;

public:

  DigitaliserView(QWidget *, WindowManager *);
  virtual ~DigitaliserView();

private:

  virtual void		paintEvent(QPaintEvent *);
};

#endif

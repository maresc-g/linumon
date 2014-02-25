//
// JobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:54:38 2014 guillaume marescaux
// Last update Tue Feb 25 14:55:18 2014 guillaume marescaux
//

#ifndef 		__JOBVIEW_HH__
# define 		__JOBVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_jobview.h"
#include		"Qt/WindowManager.hh"

class			JobView : public QWidget
{
  Q_OBJECT

public:

  JobView(QWidget *, WindowManager *wMan);
  virtual ~JobView();

private:

  Ui::jobview		ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);
};

#endif

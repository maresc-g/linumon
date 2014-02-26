//
// JobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:54:38 2014 guillaume marescaux
// Last update Tue Feb 25 16:27:18 2014 guillaume marescaux
//

#ifndef 		__JOBVIEW_HH__
# define 		__JOBVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_jobview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/Job.hh"

class			JobView : public QWidget
{
  Q_OBJECT

public:

  JobView(QWidget *, WindowManager *wMan);
  virtual ~JobView();

  void			setInfos(Job const &job);

private:

  Ui::jobview		ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_craft_clicked();
};

#endif

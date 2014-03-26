//
// JobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:54:38 2014 guillaume marescaux
// Last update Wed Mar 26 14:04:45 2014 guillaume marescaux
//

#ifndef 		__JOBVIEW_HH__
# define 		__JOBVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_jobview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/Job.hh"
#include		"Qt/Views/CraftView.hh"

class			CraftView;

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
  CraftView		*_currentCraft;
  Job const		*_job;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_craft_clicked();
  void			on_b_quit_clicked();
  void			handleChange();
};

#endif

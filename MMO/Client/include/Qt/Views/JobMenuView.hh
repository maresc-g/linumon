//
// JobMenuView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 12:56:42 2014 guillaume marescaux
// Last update Thu Feb 27 13:13:28 2014 guillaume marescaux
//

#ifndef 		__JOBMENUVIEW_HH__
# define 		__JOBMENUVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_jobmenuview.h"
#include		"Qt/WindowManager.hh"

class			JobMenuView : public QWidget
{
  Q_OBJECT

public:

  JobMenuView(QWidget *, WindowManager *wMan);
  virtual ~JobMenuView();

private:

  Ui::jobmenuview	ui;
  WindowManager		*_wMan;

private:

  void			initJob(std::string const &name);
  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_alch_clicked();
  void			on_b_dev_clicked();
  void			on_b_crafter1_clicked();
  void			on_b_crafter2_clicked();
  void			on_b_mineur_clicked();
  void			on_b_trapper_clicked();
  void			on_b_herbo_clicked();
};

#endif

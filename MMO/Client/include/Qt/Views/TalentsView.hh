//
// TalentsView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 17 22:31:32 2014 guillaume marescaux
// Last update Tue Mar 18 10:53:08 2014 guillaume marescaux
//

#ifndef 		__TALENTSVIEW_HH__
# define 		__TALENTSVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_talentsview.h"
#include		"Qt/WindowManager.hh"
#include		"Stats/TalentTree.hh"

class			WindowManager;

class			TalentsView : public QWidget
{
  Q_OBJECT

public:
  TalentsView(QWidget *, WindowManager *wman);
  virtual ~TalentsView();

private:
  Ui::talentsview	ui;
  WindowManager		*_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);

public:

  void			initTalents(TalentTree const &tree);
};

#endif

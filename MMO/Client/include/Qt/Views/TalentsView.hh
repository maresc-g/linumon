//
// TalentsView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 17 22:31:32 2014 guillaume marescaux
// Last update Thu Mar 20 15:51:22 2014 guillaume marescaux
//

#ifndef 		__TALENTSVIEW_HH__
# define 		__TALENTSVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_talentsview.h"
#include		"Qt/WindowManager.hh"
#include		"Stats/TalentTree.hh"
#include		"Qt/Views/TalentView.hh"

class			WindowManager;
class			TalentView;

class			TalentsView : public QWidget
{
  Q_OBJECT

public:
  TalentsView(QWidget *, WindowManager *wman);
  virtual ~TalentsView();

private:
  Ui::talentsview	ui;
  WindowManager		*_wMan;
  std::list<TalentView *>	*_talentViews;

private:
  virtual void		paintEvent(QPaintEvent *);

public:

  void			initTalents(TalentTree const &tree);
};

#endif

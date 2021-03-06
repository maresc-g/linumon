//
// CraftView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Feb 26 14:22:32 2014 guillaume marescaux
// Last update Thu Mar 13 12:38:00 2014 guillaume marescaux
//

#ifndef 		__CRAFTVIEW_HH__
# define 		__CRAFTVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_craftview.h"
#include		"Qt/WindowManager.hh"

class			CraftView : public QWidget
{
  Q_OBJECT

public:

  CraftView(QWidget *, WindowManager *wMan);
  virtual ~CraftView();

private:

  Ui::craftview		ui;
  WindowManager		*_wMan;
  Craft const		*_craft;
  std::list<StackView*>	*_stacks;

private:

  virtual void		paintEvent(QPaintEvent *);

public:

  void			setInfos(Craft const &craft);
  Craft const		&getCraft(void) const;
};

#endif

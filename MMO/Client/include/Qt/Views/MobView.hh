//
// MobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:41:39 2014 guillaume marescaux
// Last update Fri Feb 28 15:52:48 2014 guillaume marescaux
//

#ifndef 		__MOBVIEW_HH__
# define 		__MOBVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_itemview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/AItem.hh"

class			MobView : public QWidget
{
  Q_OBJECT

public:

  MobView(QWidget *, WindowManager *wMan, unsigned int nb, Mob *mob);
  MobView(QWidget *parent, WindowManager *wMan);
  virtual ~MobView();
  AItem const		&getItem(void) const;

private:

  Ui::itemview		ui;
  WindowManager		*_wMan;
  Mob			*_mob;
  unsigned int		_nb;

private:

  virtual void		paintEvent(QPaintEvent *);
//   virtual void		enterEvent(QEvent *event);
//   virtual void		mouseDoubleClickEvent(QMouseEvent *event);
//   void			setInfos(AItem *item, unsigned int nb);
// public:
//   virtual void		resize(int, int);

// public slots:
//   void			makeDrag();
// protected:
//   void			dropEvent(QDropEvent *de);
//   void			dragMoveEvent(QDragMoveEvent *de);
//   void			dragEnterEvent(QDragEnterEvent *event);
};

#endif

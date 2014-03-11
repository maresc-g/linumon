//
// MobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:41:39 2014 guillaume marescaux
// Last update Tue Mar 11 13:49:25 2014 guillaume marescaux
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

  MobView(QWidget *, WindowManager *wMan, Mob const *mob);
  MobView(QWidget *parent, WindowManager *wMan);
  virtual ~MobView();

private:

  Ui::itemview		ui;
  WindowManager		*_wMan;
  Mob const		*_mob;
  int			_x;
  int			_y;

public:

  virtual void		resize(int, int);
  virtual void		move(int, int);
  void			setInfos(Mob const *mob);

private:
  virtual void		paintEvent(QPaintEvent *);

private slots:
  void			displayMenu(const QPoint&);

protected:
  virtual void		dropEvent(QDropEvent *de);
  virtual void		dragMoveEvent(QDragMoveEvent *de);
  virtual void		dragEnterEvent(QDragEnterEvent *event);

//   virtual void		enterEvent(QEvent *event);
//   virtual void		mouseDoubleClickEvent(QMouseEvent *event);
//   void			setInfos(AItem *item, unsigned int nb);

// public slots:
//   void			makeDrag();
};

#endif

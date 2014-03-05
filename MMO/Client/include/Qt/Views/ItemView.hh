//
// ItemView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:16:30 2014 guillaume marescaux
// Last update Mon Mar  3 13:41:48 2014 guillaume marescaux
//

#ifndef 		__ITEMVIEW_HH__
# define 		__ITEMVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_itemview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/AItem.hh"

class			ItemView : public QWidget
{
  Q_OBJECT

public:

  ItemView(QWidget *, WindowManager *wMan, unsigned int nb, AItem *item);
  ItemView(QWidget *parent, WindowManager *wMan);
  virtual ~ItemView();
  AItem const		&getItem(void) const;

private:

  Ui::itemview		ui;
  WindowManager		*_wMan;
  AItem			*_item;
  unsigned int		_nb;
  int			_x;
  int			_y;

private:

  virtual void		paintEvent(QPaintEvent *);
  virtual void		enterEvent(QEvent *event);
  virtual void		mouseDoubleClickEvent(QMouseEvent *event);
  void			setInfos(AItem *item, unsigned int nb);
public:
  virtual void		resize(int, int);
  virtual void		move(int, int);

// public slots:
//   void			makeDrag();
// protected:
//   void			dropEvent(QDropEvent *de);
//   void			dragMoveEvent(QDragMoveEvent *de);
//   void			dragEnterEvent(QDragEnterEvent *event);
};

#endif

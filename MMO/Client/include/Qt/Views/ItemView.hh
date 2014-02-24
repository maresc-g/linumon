//
// ItemView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:16:30 2014 guillaume marescaux
// Last update Mon Feb 24 15:11:13 2014 guillaume marescaux
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

  ItemView(QWidget *, WindowManager *wMan, unsigned int nb, AItem *item = NULL);
  ItemView(QWidget *parent, WindowManager *wMan, AItem *item = NULL);
  virtual ~ItemView();

private:

  Ui::itemview		ui;
  WindowManager		*_wMan;
  AItem			*_item;
  unsigned int		_nb;

private:

  virtual void		paintEvent(QPaintEvent *);
  virtual void		enterEvent(QEvent *event);
};

#endif

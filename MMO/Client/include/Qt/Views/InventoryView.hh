//
// InventoryView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:46:00 2014 guillaume marescaux
// Last update Thu Feb 13 14:34:01 2014 guillaume marescaux
//

#ifndef 		__INVENTORYVIEW_HH__
# define 		__INVENTORYVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_inventoryview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/ItemView.hh"

class			WindowManager;

class			InventoryView : public QWidget
{
  Q_OBJECT

public:
  InventoryView(QWidget *, WindowManager *wman = NULL);
  ~InventoryView();

private:
  Ui::inventoryview	ui;
  WindowManager		*_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);
};

#endif

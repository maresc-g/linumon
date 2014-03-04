//
// StuffView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:08:03 2014 guillaume marescaux
// Last update Tue Mar  4 13:58:23 2014 guillaume marescaux
//

#ifndef 		__STUFFVIEW_HH__
# define 		__STUFFVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_stuffview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/ItemView.hh"
#include		"Entities/Player.hh"

class			WindowManager;
class			ItemView;

class			StuffView : public QWidget
{
  Q_OBJECT

public:
  StuffView(QWidget *, WindowManager *wman = NULL);
  virtual ~StuffView();

private:
  Ui::stuffview		ui;
  WindowManager		*_wMan;
  std::list<QLabel *>	*_labels;
  std::list<ItemView *>	*_items;
  AEntity const		*_last;
  bool			_changed;

private:
  virtual void		paintEvent(QPaintEvent *);
  void			setEquipment(Equipment const *equipment);
  void			setItem(Equipment const *equipment, Stuff::eStuff stuff, int x, int y);

public:
  void			initStuff(Player const &player);
  void			initStuff(Mob const &mob);
  void			itemAction(ItemView *);
  void			setChanged(bool changed);
};

#endif

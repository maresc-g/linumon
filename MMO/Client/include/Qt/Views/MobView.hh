//
// MobView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:41:39 2014 guillaume marescaux
// Last update Wed Mar 19 15:29:40 2014 cyril jourdain
//

#ifndef 		__MOBVIEW_HH__
# define 		__MOBVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_stackview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/AItem.hh"
#include		"ParentInfos.hh"

class			MobView : public QWidget
{
  Q_OBJECT

public:

  MobView(QWidget *, WindowManager *wMan, Mob const *mob);
  MobView(QWidget *parent, WindowManager *wMan);
  virtual ~MobView();

private:

  Ui::stackview		ui;
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
  virtual void		mousePressEvent(QMouseEvent *);
  void			makeDrag();
  ParentInfos		*getNameFirstParent(QWidget *parent);

private slots:
  void			displayMenu(const QPoint&);

signals:
  void			clicked(unsigned int id);

protected:
  virtual void		dropEvent(QDropEvent *de);
  virtual void		dragMoveEvent(QDragMoveEvent *de);
  virtual void		dragEnterEvent(QDragEnterEvent *event);
};

#endif

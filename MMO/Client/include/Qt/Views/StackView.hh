//
// StackView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:16:30 2014 guillaume marescaux
// Last update Wed Mar 12 22:05:27 2014 guillaume marescaux
//

#ifndef 		__STACKVIEW_HH__
# define 		__STACKVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_stackview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/Stack.hh"
#include		"ParentInfos.hh"

class			StackView : public QWidget
{
  Q_OBJECT

public:

  StackView(QWidget *, WindowManager *wMan, Stack const *stack);
  StackView(QWidget *parent, WindowManager *wMan);
  virtual ~StackView();
  Stack const		&getStack(void) const;

private:

  Ui::stackview		ui;
  WindowManager		*_wMan;
  Stack	const		*_stack;
  int			_x;
  int			_y;

private:

  virtual void		paintEvent(QPaintEvent *);
  virtual void		enterEvent(QEvent *event);
  virtual void		mouseDoubleClickEvent(QMouseEvent *event);
  void			setInfos(Stack const *stack);
  virtual void		mousePressEvent(QMouseEvent *);
  void			makeDrag();
  ParentInfos		*getNameFirstParent(QWidget *parent);

public:
  virtual void		resize(int, int);
  virtual void		move(int, int);

protected:
  void			dropEvent(QDropEvent *de);
  void			dragMoveEvent(QDragMoveEvent *de);
  void			dragEnterEvent(QDragEnterEvent *event);
};

#endif

//
// SplitStackView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:56:36 2014 guillaume marescaux
<<<<<<< HEAD
// Last update Fri Mar 14 14:40:36 2014 guillaume marescaux
=======
// Last update Fri Mar 14 13:00:18 2014 laurent ansel
>>>>>>> 13796ed8b9ed7e84e0c0e9042b0250140186fbe3
//

#ifndef 		__SPLITSTACKVIEW_HH__
# define 		__SPLITSTACKVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_splitstackview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/StackView.hh"
#include		"ParentInfos.hh"

class			SplitStackView : public QWidget
{
  Q_OBJECT

public:

  SplitStackView(QWidget *, WindowManager *wMan);
  virtual ~SplitStackView();

private:

  Ui::splitstackview	ui;
  WindowManager		*_wMan;
<<<<<<< HEAD
  StackView		*_source;
  StackView		*_dest;
=======
  Stack<AItem> const	*_stack;
>>>>>>> 13796ed8b9ed7e84e0c0e9042b0250140186fbe3

private:

  virtual void		paintEvent(QPaintEvent *);
  ParentInfos		*getNameFirstParent(QWidget *parent);

private slots:

  void			on_b_accept_clicked();
  void			on_b_cancel_clicked();

public:

<<<<<<< HEAD
  void			setInfos(StackView *source, StackView *dest);
=======
  void			setInfos(Stack<AItem> const *stack);
>>>>>>> 13796ed8b9ed7e84e0c0e9042b0250140186fbe3
};

#endif

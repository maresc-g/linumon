//
// FrameMobs.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 14:42:55 2014 guillaume marescaux
// Last update Thu Mar 13 14:24:49 2014 guillaume marescaux
//

#ifndef 		__FRAMEMOBS_HH__
# define 		__FRAMEMOBS_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		<QFrame>
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/ParentInfos.hh"

class			FrameMobs : public QFrame
{
  Q_OBJECT

private:

  WindowManager		*_wMan;

public:

  FrameMobs(QWidget * parent, WindowManager *wMan);
  virtual ~FrameMobs();

private:

  virtual void		paintEvent(QPaintEvent *);
  ParentInfos		*getNameFirstParent(QWidget *parent);

protected:
  void			dropEvent(QDropEvent *de);
  void			dragMoveEvent(QDragMoveEvent *de);
  void			dragEnterEvent(QDragEnterEvent *event);
};

#endif

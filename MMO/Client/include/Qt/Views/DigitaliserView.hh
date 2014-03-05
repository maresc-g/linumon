//
// DigitaliserView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:26:29 2014 guillaume marescaux
// Last update Mon Mar  3 13:59:02 2014 guillaume marescaux
//

#ifndef 		__DIGITALISERVIEW_HH__
# define 		__DIGITALISERVIEW_HH__

#include		<list>
#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		<QScrollArea>
#include		<QFrame>
#include		"ui_digitaliserview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/MobView.hh"

class			MobView;

class			DigitaliserView : public QWidget
{
  Q_OBJECT

private:

  WindowManager		*_wMan;
  QScrollArea		*_scrollArea;
  QFrame		*_frame;
  Ui::digitaliserview	ui;
  std::list<MobView *>	*_mobs;
  std::list<MobView *>	*_battleMobs;

public:

  DigitaliserView(QWidget *, WindowManager *);
  virtual ~DigitaliserView();
  void			initDigit(Digitaliser const &digit);

private:

  virtual void		paintEvent(QPaintEvent *);
};

#endif

//
// DigitaliserView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:26:29 2014 guillaume marescaux
// Last update Wed Mar 12 16:30:40 2014 guillaume marescaux
//

#ifndef 		__DIGITALISERVIEW_HH__
# define 		__DIGITALISERVIEW_HH__

#include		<list>
#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		<QScrollArea>
#include		"Qt/Views/FrameMobs.hh"
#include		"ui_digitaliserview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/MobView.hh"

class			MobView;
class			FrameMobs;

class			DigitaliserView : public QWidget
{
  Q_OBJECT

private:

  WindowManager		*_wMan;
  QScrollArea		*_scrollArea;
  FrameMobs		*_f_battleMobs;
  FrameMobs		*_frame;
  Ui::digitaliserview	ui;
  std::list<MobView *>	*_mobs;
  std::list<MobView *>	*_battleMobs;
  std::list<MobView *>	*_hiddenMobs;
  std::list<MobView *>	*_hiddenBattleMobs;

public:

  DigitaliserView(QWidget *, WindowManager *);
  virtual ~DigitaliserView();
  void			initDigit(Digitaliser const &digit);

private:

  virtual void		paintEvent(QPaintEvent *);
};

#endif

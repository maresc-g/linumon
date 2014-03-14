//
// TradeView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:27:33 2014 guillaume marescaux
// Last update Fri Mar 14 15:46:24 2014 guillaume marescaux
//

#ifndef 			__TRADEVIEW_HH__
# define 			__TRADEVIEW_HH__

#include			<Qt/qwidget.h>
#include			<Qt/qpainter.h>
#include			"ui_tradeview.h"
#include			"Qt/WindowManager.hh"
#include			"Qt/Views/MobView.hh"
#include			"Qt/Views/StackView.hh"
#include			"Mutex/MutexVar.hpp"
#include			"Trade/Trade.hh"

class				TradeView : public QWidget
{
  Q_OBJECT

public:

  TradeView(QWidget *, WindowManager *wMan);
  virtual ~TradeView();

private:

  Ui::tradeview			ui;
  WindowManager			*_wMan;
  std::list<MobView *>		*_mobViews;
  std::list<MobView *>		*_otherMobViews;
  std::list<StackView *>	*_stackViews;
  std::list<StackView *>	*_otherStackViews;
  std::list<MobView *>		*_hiddenMobViews;
  std::list<MobView *>		*_hiddenOtherMobViews;
  std::list<StackView *>	*_hiddenStackViews;
  std::list<StackView *>	*_hiddenOtherStackViews;

private:

  virtual void			paintEvent(QPaintEvent *);

private slots:

  void				on_b_accept_clicked();
  void				on_b_cancel_clicked();

public:

  void				reset(void);
  void				setInfos(MutexVar<Trade *> *trade);
  void				putStackToTrade(Stack const *stack);
  void				getStackFromTrade(Stack const *stack);
  void				handleMobChange(MobView *source, MobView *dest);
};

#endif

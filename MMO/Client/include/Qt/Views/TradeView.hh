//
// TradeView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:27:33 2014 guillaume marescaux
// Last update Wed Mar 12 21:58:03 2014 guillaume marescaux
//

#ifndef 		__TRADEVIEW_HH__
# define 		__TRADEVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_tradeview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/MobView.hh"
#include		"Qt/Views/StackView.hh"

class			TradeView : public QWidget
{
  Q_OBJECT

public:

  TradeView(QWidget *, WindowManager *wMan);
  virtual ~TradeView();

private:

  Ui::tradeview		ui;
  WindowManager		*_wMan;
  std::list<MobView *>	*_mobs;
  std::list<MobView *>	*_otherMobs;
  std::list<StackView *>	*_stacks;
  std::list<StackView *>	*_otherStacks;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_accept_clicked();
  void			on_b_cancel_clicked();

public:

  void			setInfos(std::string const &name);
  void			handleStackChange(StackView *source, StackView *dest);
  void			handleMobChange(MobView *source, MobView *dest);
};

#endif

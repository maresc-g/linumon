//
// PlayerClickView.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Feb 28 23:00:43 2014 cyril jourdain
// Last update Sun Mar  2 14:00:34 2014 cyril jourdain
//

#ifndef 		__PLAYERCLICKVIEW_HH__
# define 		__PLAYERCLICKVIEW_HH__

#include		<QWidget>
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/TradeView.hh"

class TradeView;

class			PlayerClickView : public QWidget
{
  Q_OBJECT

private:
  WindowManager		*_wMan;
  QPushButton		*_b_aggro;
  QPushButton		*_b_trade;
  TradeView		*_tradeView;

public:
  PlayerClickView(QWidget *parent, WindowManager *);
  virtual ~PlayerClickView();

private:
  virtual void		paintEvent(QPaintEvent *);

private slots:
  void			bAggroClicked();
  void			bTradeClicked();

};

#endif

//
// TradeView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:27:33 2014 guillaume marescaux
// Last update Sat Mar  1 01:02:42 2014 cyril jourdain
//

#ifndef 		__TRADEVIEW_HH__
# define 		__TRADEVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_tradeview.h"
#include		"Qt/WindowManager.hh"

class			TradeView : public QWidget
{
  Q_OBJECT

public:

  TradeView(QWidget *, WindowManager *wMan);
  virtual ~TradeView();

private:

  Ui::tradeview		ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_accept_clicked();
  void			on_b_cancel_clicked();
};

#endif

//
// TradeView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:28:48 2014 guillaume marescaux
// Last update Fri Feb 21 14:34:00 2014 guillaume marescaux
//

#include			"Qt/Views/TradeView.hh"

TradeView::TradeView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

TradeView::~TradeView()
{
}

void				TradeView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				TradeView::on_b_accept_clicked()
{
  Client::getInstance()->accept();
}

void				TradeView::on_b_cancel_clicked()
{
  Client::getInstance()->refuse();
}

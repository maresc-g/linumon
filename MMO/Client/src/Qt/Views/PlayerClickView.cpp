//
// PlayerClickView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Feb 28 23:06:40 2014 cyril jourdain
// Last update Wed Mar 12 12:47:17 2014 guillaume marescaux
//

#include		"Qt/Views/PlayerClickView.hh"

PlayerClickView::PlayerClickView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent), _wMan(wMan), _b_aggro(new QPushButton(this)), _b_trade(new QPushButton(this)),
  _tradeView(new TradeView(parent, wMan))
{
  _b_aggro->move(0,32);
  _b_aggro->resize(100,32);
  _b_aggro->setText("Fight !");
  _b_trade->resize(100,32);
  _b_trade->setText("Trade");
  _b_aggro->show();
  _b_trade->show();
  _tradeView->hide();

  connect(_b_trade, SIGNAL(clicked()), this, SLOT(bTradeClicked()));
  connect(_b_aggro, SIGNAL(clicked()), this, SLOT(bAggroClicked()));
}

PlayerClickView::~PlayerClickView()
{
}

void				PlayerClickView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				PlayerClickView::bAggroClicked()
{
  std::cout << "AGGRO TIME" << std::endl;
}

void				PlayerClickView::bTradeClicked()
{
  std::cout << "SO UR TELLIN ME U WANNA TRADE ? GOOBY PLZ" << std::endl;
  _tradeView->move(1400, 0);
  _tradeView->show();
  _tradeView->setInfos("Alexis le noob overkill");
}

//
// TradeView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:28:48 2014 guillaume marescaux
// Last update Wed Mar 12 12:54:30 2014 guillaume marescaux
//

#include			"Qt/Views/TradeView.hh"

TradeView::TradeView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan),
  _mobs(new std::list<MobView *>), _otherMobs(new std::list<MobView *>),
  _items(new std::list<ItemView *>), _otherItems(new std::list<ItemView *>)
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

void				TradeView::setInfos(std::string const &name)
{
  ItemView			*item;
  MobView			*mob;

  ui.l_name->setText((**_wMan->getMainPlayer())->getName().c_str());
  ui.l_otherName->setText(name.c_str());
  ui.le_money->setText("0");
  ui.l_otherMoney->setText("0");
  _mobs->clear();
  _otherMobs->clear();
  _items->clear();
  _otherItems->clear();
  for (int i = 0 ; i < 15 ; i++)
    {
      item = new ItemView(ui.f_items, _wMan);
      _items->push_back(item);
      item->move(i % 3 * 50 + i % 3, i / 3 * 50);
      item->resize(50, 50);
      item->show();
      item = new ItemView(ui.f_otherItems, _wMan);
      _otherItems->push_back(item);
      item->move(i % 3 * 50 + i % 3, i / 3 * 50);
      item->resize(50, 50);
      item->show();
      mob = new MobView(ui.f_mobs, _wMan);
      _mobs->push_back(mob);
      mob->move(i % 3 * 50 + i % 3, i / 3 * 50);
      mob->resize(50, 50);
      mob->show();
      mob = new MobView(ui.f_otherMobs, _wMan);
      _otherMobs->push_back(mob);
      mob->move(i % 3 * 50 + i % 3, i / 3 * 50);
      mob->resize(50, 50);
      mob->show();
    }
}

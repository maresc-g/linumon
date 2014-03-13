//
// TradeView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:28:48 2014 guillaume marescaux
// Last update Wed Mar 12 22:35:45 2014 guillaume marescaux
//

#include			"Qt/Views/TradeView.hh"

TradeView::TradeView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan),
  _mobs(new std::list<MobView *>), _otherMobs(new std::list<MobView *>),
  _stacks(new std::list<StackView *>), _otherStacks(new std::list<StackView *>)
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
  StackView			*stack;
  MobView			*mob;

  ui.l_name->setText((**_wMan->getMainPlayer())->getName().c_str());
  ui.l_otherName->setText(name.c_str());
  ui.le_money->setText("0");
  ui.l_otherMoney->setText("0");
  _mobs->clear();
  _otherMobs->clear();
  _stacks->clear();
  _otherStacks->clear();
  for (int i = 0 ; i < 15 ; i++)
    {
      stack = new StackView(ui.f_stacks, _wMan);
      _stacks->push_back(stack);
      stack->move(i % 3 * 50 + i % 3, i / 3 * 50);
      stack->resize(50, 50);
      stack->show();
      stack = new StackView(ui.f_otherStacks, _wMan);
      _otherStacks->push_back(stack);
      stack->move(i % 3 * 50 + i % 3, i / 3 * 50);
      stack->resize(50, 50);
      stack->show();
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

void				TradeView::handleStackChange(StackView *source, StackView *dest)
{
}

void				TradeView::handleMobChange(MobView *source, MobView *dest)
{
}

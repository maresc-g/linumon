//
// TradeView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb 20 13:28:48 2014 guillaume marescaux
// Last update Fri Mar 14 16:14:15 2014 guillaume marescaux
//

#include			"Qt/Views/TradeView.hh"

TradeView::TradeView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan),
  _mobViews(new std::list<MobView *>), _otherMobViews(new std::list<MobView *>),
  _stackViews(new std::list<StackView *>), _otherStackViews(new std::list<StackView *>),
  _hiddenMobViews(new std::list<MobView *>), _hiddenOtherMobViews(new std::list<MobView *>),
  _hiddenStackViews(new std::list<StackView *>), _hiddenOtherStackViews(new std::list<StackView *>)
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

void				TradeView::reset()
{
}

void				TradeView::setInfos(MutexVar<Trade *> *trade)
{
  StackView			*stack;
  MobView			*mob;

  ui.l_name->setText((**_wMan->getMainPlayer())->getName().c_str());
  ui.l_otherName->setText((**trade)->getName().c_str());
  ui.le_money->setText("0");
  ui.l_otherMoney->setText("0");

  _mobViews->clear();
  _otherMobViews->clear();
  _stackViews->clear();
  _otherStackViews->clear();

  for (auto it = _hiddenMobViews->begin() ; it != _hiddenMobViews->end() ; it++)
    delete *it;
  _hiddenMobViews->clear();
  for (auto it = _mobViews->begin() ; it != _mobViews->end() ; it++)
    {
      (*it)->hide();
      _hiddenMobViews->push_back(*it);
    }
  _mobViews->clear();

  for (auto it = _hiddenOtherMobViews->begin() ; it != _hiddenOtherMobViews->end() ; it++)
    delete *it;
  _hiddenOtherMobViews->clear();
  for (auto it = _otherMobViews->begin() ; it != _otherMobViews->end() ; it++)
    {
      (*it)->hide();
      _hiddenOtherMobViews->push_back(*it);
    }
  _otherMobViews->clear();

  for (auto it = _hiddenStackViews->begin() ; it != _hiddenStackViews->end() ; it++)
    delete *it;
  _hiddenStackViews->clear();
  for (auto it = _stackViews->begin() ; it != _stackViews->end() ; it++)
    {
      (*it)->hide();
      _hiddenStackViews->push_back(*it);
    }
  _stackViews->clear();

  for (auto it = _hiddenOtherStackViews->begin() ; it != _hiddenOtherStackViews->end() ; it++)
    delete *it;
  _hiddenOtherStackViews->clear();
  for (auto it = _otherStackViews->begin() ; it != _otherStackViews->end() ; it++)
    {
      (*it)->hide();
      _hiddenOtherStackViews->push_back(*it);
    }
  _otherStackViews->clear();

  auto				itStacks = (**trade)->getPlayerStacks().begin();
  auto				itOtherStacks = (**trade)->getOtherStacks().begin();
  auto				itMobs = (**trade)->getPlayerMobs().begin();
  auto				itOtherMobs = (**trade)->getOtherMobs().begin();

  for (int i = 0 ; i < 15 ; i++)
    {
      if (itStacks != (**trade)->getPlayerStacks().end())
	{
	  stack = new StackView(ui.f_stacks, _wMan, *itStacks);
	  itStacks++;
	}
      else
	stack = new StackView(ui.f_stacks, _wMan);
      _stackViews->push_back(stack);
      stack->move(i % 3 * 50 + i % 3, i / 3 * 50);
      stack->resize(50, 50);
      stack->show();

      if (itOtherStacks != (**trade)->getOtherStacks().end())
	{
	  stack = new StackView(ui.f_otherStacks, _wMan, *itStacks);
	  itOtherStacks++;
	}
      else
	stack = new StackView(ui.f_otherStacks, _wMan);
      _otherStackViews->push_back(stack);
      stack->move(i % 3 * 50 + i % 3, i / 3 * 50);
      stack->resize(50, 50);
      stack->show();

      if (itMobs != (**trade)->getPlayerMobs().end())
	{
	  mob = new MobView(ui.f_mobs, _wMan, *itMobs);
	  itMobs++;
	}
      else
	mob = new MobView(ui.f_mobs, _wMan);
      _mobViews->push_back(mob);
      mob->move(i % 3 * 50 + i % 3, i / 3 * 50);
      mob->resize(50, 50);
      mob->show();

      if (itOtherMobs != (**trade)->getOtherMobs().end())
	{
	  mob = new MobView(ui.f_otherMobs, _wMan, *itOtherMobs);
	  itOtherMobs++;
	}
      else
	mob = new MobView(ui.f_otherMobs, _wMan);
      _otherMobViews->push_back(mob);
      mob->move(i % 3 * 50 + i % 3, i / 3 * 50);
      mob->resize(50, 50);
      mob->show();
    }
}

// void				TradeView::putStackToTrade(Stack<AItem> const *stack)
// {
//   (**trade)->getPlayerStacks()->push_back(stack);
//   setInfos(_name);
// }

// void				TradeView::getStackFromTrade(Stack<AItem> const *stack)
// {
//   auto it = find_if((**trade)->getPlayerStacks()->begin(), (**trade)->getPlayerStacks()->end(), [&](Stack<AItem> const *val){
//       if (val->getId() == stack->getId())
//   	return true;
//       return false;
//     });

//   if (it != (**trade)->getPlayerStacks()->end())
//     {
//       (**trade)->getPlayerStacks()->erase(it);
//       setInfos(_name);
//     }
// }

void				TradeView::handleMobChange(MobView *, MobView *)
{
}

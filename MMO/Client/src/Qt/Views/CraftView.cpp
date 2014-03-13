//
// CraftView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Feb 26 14:24:07 2014 guillaume marescaux
// Last update Thu Mar 13 12:41:24 2014 guillaume marescaux
//

#include			"Qt/Views/CraftView.hh"

CraftView::CraftView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _craft(NULL), _stacks(new std::list<StackView *>)
{
  ui.setupUi(this);
}

CraftView::~CraftView()
{
  for (auto it = _stacks->begin() ; it != _stacks->end() ; ++it)
    delete *it;
  delete _stacks;
}

void				CraftView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				CraftView::setInfos(Craft const &craft)
{
  _craft = &craft;
  ui.l_name->setText(craft.getName().c_str());
  auto				stacks = craft.getIngredients();
  StackView			*stack;
  int				i = 0;

  for (auto it = _stacks->begin() ; it != _stacks->end() ; ++it)
    delete *it;
  _stacks->clear();
  for (auto it = stacks.begin() ; it != stacks.end() ; ++it)
    {
      stack = new StackView(ui.f_craft, _wMan, (*it));
      stack->move(i * ITEM_SIZE + i, 0);
      stack->resize(ITEM_SIZE, ITEM_SIZE);
      stack->show();
      _stacks->push_back(stack);
      i++;
    }
}

Craft const			&CraftView::getCraft(void) const { return (*_craft); }

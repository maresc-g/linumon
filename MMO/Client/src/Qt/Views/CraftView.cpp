//
// CraftView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Feb 26 14:24:07 2014 guillaume marescaux
// Last update Wed Mar 12 23:01:46 2014 laurent ansel
//

#include			"Qt/Views/CraftView.hh"

CraftView::CraftView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _craft(NULL)
{
  ui.setupUi(this);
}

CraftView::~CraftView()
{
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
  auto				items = craft.getIngredients();
  ItemView			*item;
  int				i = 0;

  for (auto it = items.begin() ; it != items.end() ; it++)
    {
      item = new ItemView(ui.f_craft, _wMan, (*it)->getNb(), (*it)->getItem());
      item->move(i * ITEM_SIZE + i, 0);
      item->resize(ITEM_SIZE, ITEM_SIZE);
      i++;
    }
}

Craft const			&CraftView::getCraft(void) const { return (*_craft); }

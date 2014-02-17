//
// InventoryView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:47:37 2014 guillaume marescaux
// Last update Mon Feb 17 14:34:06 2014 guillaume marescaux
//

#include			"Qt/Views/InventoryView.hh"

InventoryView::InventoryView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _toolbar(new QToolBar(this))
{
  ui.setupUi(this);
}

InventoryView::~InventoryView()
{
}

void				InventoryView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				InventoryView::initInventory()
{
  MutexVar<Player *>		*player = _wMan->getMainPlayer();
  Inventory const		inventory = (**player)->getInventory();
  ui.money->setText(std::to_string(inventory.getMoney()).c_str());
  unsigned int			limit = inventory.getLimit();
  std::list<AItem *> const	items = inventory.getInventory();
  auto				it = items.begin();
  ItemView			*item;

  for (unsigned int i = 0 ; i < limit ; i++)
    {
      if (it != items.end())
	{
	  item = new ItemView(ui.frame, _wMan, *it);
	  it++;
	}
      else
	  item = new ItemView(ui.frame, _wMan);
      item->move(i % 5 * 50 + i % 5, i / 5 * 50);
      item->resize(50, 50);
    }
  ui.frame->resize(5 * 50 + 5, limit / 5 * 50);
  ui.frame->move(5, 5 + 50);
  this->resize(5 * 50 + 20, limit / 5 * 50 + 150);
  ui.money->move(5 * 50 - 120, limit / 5 * 50 + 20 + 50);
}

//
// InventoryView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:47:37 2014 guillaume marescaux
// Last update Thu Feb 13 14:35:25 2014 guillaume marescaux
//

#include			"Qt/Views/InventoryView.hh"

InventoryView::InventoryView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
  // ui.grid->addWidget(new ItemView(this, wMan), 0, 0);
  // ui.grid->addWidget(new ItemView(this, wMan), 1, 0);
  MutexVar<Player *>		*player = wMan->getMainPlayer();
  // Inventory const		inventory = (**player)->getInventory();
  // ui.money->setText(std::to_string(inventory.getMoney()).c_str());
  ui.money->setText(std::to_string(1000).c_str());  
  // unsigned int			limit = inventory.getLimit();
  unsigned int			limit = 50;
  for (unsigned int i = 0 ; i < limit ; i++)
    {
      // ui.grid->addWidget(new ItemView(this, wMan), i / 5 , i % 5);      
      ItemView			*item = new ItemView(ui.frame, wMan);
      item->move(i % 5 * 50 + i % 5, i / 5 * 50);
      item->resize(50, 50);
    }
  // setToolTipText("te
  ui.frame->resize(5 * 50 + 5, limit / 5 * 50);
  ui.frame->move(5, 5);
  this->resize(5 * 50 + 20, limit / 5 * 50 + 100);
  ui.money->move(5 * 50 - 120, limit / 5 * 50 + 20);
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

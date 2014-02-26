//
// InventoryView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:47:37 2014 guillaume marescaux
// Last update Wed Feb 26 16:50:39 2014 guillaume marescaux
//

#include			"Qt/Views/InventoryView.hh"

InventoryView::InventoryView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _toolbar(new QToolBar(this))
{
  ui.setupUi(this);
  QPixmap			closepix("./Res/close-button.png");
  QWidget* spacer = new QWidget(this);

  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  _toolbar->addWidget(spacer);

  QAction			*action = _toolbar->addAction(closepix, "close");

  connect(action, SIGNAL(triggered()), this, SLOT(hide()));
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
  Inventory const		*inventory = &(**player)->getInventory();
  ui.money->setText(std::to_string(inventory->getMoney()).c_str());
  unsigned int			limit = inventory->getLimit();
  std::list<std::pair<AItem *, unsigned int> > const	items = inventory->getInventory();
  auto				it = items.begin();
  ItemView			*item;

  for (unsigned int i = 0 ; i < limit ; i++)
    {
      if (it != items.end())
      	{
      	  item = new ItemView(ui.frame, _wMan, it->second, it->first);
      	  it++;
      	}
      else
	  item = new ItemView(ui.frame, _wMan);
      item->move(i % 5 * ITEM_SIZE + i % 5, i / 5 * ITEM_SIZE);
      item->resize(ITEM_SIZE, ITEM_SIZE);
    }
  ui.frame->resize(5 * ITEM_SIZE + 5, limit / 5 * ITEM_SIZE);
  ui.frame->move(5, 5 + 40);
  this->resize(5 * ITEM_SIZE + 20, limit / 5 * ITEM_SIZE + 100);
  ui.money->move(5 * ITEM_SIZE - 120, limit / 5 * ITEM_SIZE + 20 + 40);
}

//
// InventoryView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:47:37 2014 guillaume marescaux
// Last update Wed Mar 12 20:29:43 2014 laurent ansel
//

#include			"Qt/Views/InventoryView.hh"

InventoryView::InventoryView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _items(new std::list<ItemView *>), _hidden(new std::list<ItemView *>)
{
  ui.setupUi(this);
}

InventoryView::~InventoryView()
{
  for (auto it = _items->begin() ; it != _items->end() ; it++)
    delete *it;
  delete _items;
  for (auto it = _hidden->begin() ; it != _hidden->end() ; it++)
    delete *it;
  delete _hidden;
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
  auto				items = inventory->getInventory();
  auto				it = items.begin();
  ItemView			*item;

  for (auto it = _hidden->begin() ; it != _hidden->end() ; it++)
    delete *it;
  _hidden->clear();
  for (auto it = _items->begin() ; it != _items->end() ; it++)
    {
      (*it)->hide();
      _hidden->push_back(*it);
    }
  _items->clear();
  for (unsigned int i = 0 ; i < limit ; i++)
    {
      if (it != items.end())
      	{
      	  item = new ItemView(ui.f_items, _wMan, (*it)->getNb(), (*it)->getItem());
      	  it++;
      	}
      else
	  item = new ItemView(ui.f_items, _wMan);
      _items->push_back(item);
      item->move(i % 5 * ITEM_SIZE + i % 5, i / 5 * ITEM_SIZE);
      item->resize(ITEM_SIZE, ITEM_SIZE);
      item->show();
    }
  ui.f_items->resize(5 * ITEM_SIZE + 5, limit / 5 * ITEM_SIZE);
  ui.f_items->move(5, 5 + 40);
  this->resize(5 * ITEM_SIZE + 20, limit / 5 * ITEM_SIZE + 100);
  ui.money->move(5 * ITEM_SIZE - 120, limit / 5 * ITEM_SIZE + 20 + 40);
}

void				InventoryView::itemAction(ItemView *item)
{
  if (item->getItem().getItemType() == AItem::STUFF)
    {
      Stuff const               *stuff = static_cast<Stuff const *>(&item->getItem());
      bool                      ret;

      if (!_wMan->getSFMLView()->getStuffView()->getLast() || _wMan->getSFMLView()->getStuffView()->getLast()->getCharacterType() == ACharacter::PLAYER)
        ret = (**(_wMan->getMainPlayer()))->putPlayerEquipment(stuff->getId());
      else
        ret = (**(_wMan->getMainPlayer()))->putMobEquipment(_wMan->getSFMLView()->getStuffView()->getLast()->getId(), stuff->getId());
      if (ret)
        {
	  Client::getInstance()->stuff(eStuffAction::PUT, stuff->getId(), (**(_wMan->getMainPlayer()))->getId());
          _wMan->getSFMLView()->getStuffView()->setChanged(true);
          ACharacter const              *last = _wMan->getSFMLView()->getStuffView()->getLast();
          if (!last)
            _wMan->getSFMLView()->getStuffView()->initStuff(*static_cast<Player const *>(**_wMan->getMainPlayer()));
          else if (last->getCharacterType() == ACharacter::MOB)
            _wMan->getSFMLView()->getStuffView()->initStuff(*static_cast<Mob const *>(last));
          else
            _wMan->getSFMLView()->getStuffView()->initStuff(*static_cast<Player const *>(last));
          initInventory();
        }
    }
}

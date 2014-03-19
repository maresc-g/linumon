//
// InventoryView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:47:37 2014 guillaume marescaux
// Last update Wed Mar 19 10:30:49 2014 guillaume marescaux
//

#include <iostream>
#include			"Qt/Views/InventoryView.hh"

InventoryView::InventoryView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _stacks(new std::list<StackView *>), _hidden(new std::list<StackView *>)
{
  ui.setupUi(this);
}

InventoryView::~InventoryView()
{
  for (auto it = _stacks->begin() ; it != _stacks->end() ; it++)
    delete *it;
  delete _stacks;
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
  auto				stacks = inventory->getInventory();
  auto				it = stacks.begin();
  StackView			*stack;

  for (auto it = _hidden->begin() ; it != _hidden->end() ; it++)
    delete *it;
  _hidden->clear();
  for (auto it = _stacks->begin() ; it != _stacks->end() ; it++)
    {
      (*it)->hide();
      _hidden->push_back(*it);
    }
  _stacks->clear();
  for (unsigned int i = 0 ; i < limit ; i++)
    {
      if (it != stacks.end() && !(*it)->empty())
      	{
      	  stack = new StackView(ui.f_stacks, _wMan, (*it));
      	  it++;
      	}
      else
	{
	  if (it != stacks.end() && (*it)->empty())
	    it++;
	  stack = new StackView(ui.f_stacks, _wMan);
	}
      _stacks->push_back(stack);
      stack->move(i % 5 * ITEM_SIZE + i % 5, i / 5 * ITEM_SIZE);
      stack->resize(ITEM_SIZE, ITEM_SIZE);
      stack->show();
    }
  ui.f_stacks->resize(5 * ITEM_SIZE + 5, limit / 5 * ITEM_SIZE);
  ui.f_stacks->move(5, 5 + 40);
  this->resize(5 * ITEM_SIZE + 20, limit / 5 * ITEM_SIZE + 100);
  ui.money->move(5 * ITEM_SIZE - 120, limit / 5 * ITEM_SIZE + 20 + 40);
}

void				InventoryView::stackAction(StackView *stackView)
{
  if (stackView->getStack().getItem()->getItemType() == AItem::STUFF)
    {
      auto			*stack = &stackView->getStack();
      bool                      ret;

      if (!_wMan->getSFMLView()->getStuffView()->getLast() || _wMan->getSFMLView()->getStuffView()->getLast()->getCharacterType() == ACharacter::PLAYER)
	ret = (**(_wMan->getMainPlayer()))->putPlayerEquipment(stack->getId());
      else
        ret = (**(_wMan->getMainPlayer()))->putMobEquipment(_wMan->getSFMLView()->getStuffView()->getLast()->getId(), stack->getId());
      if (ret)
        {
	  Client::getInstance()->putStuff(stack->getId(), (**(_wMan->getMainPlayer()))->getId());
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

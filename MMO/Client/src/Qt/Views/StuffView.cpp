//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Mon Mar 10 15:02:01 2014 guillaume marescaux
//

#include			<iostream>
#include			<QMessageBox>
#include			"Qt/Views/StuffView.hh"
#include			"Client.hh"

StuffView::StuffView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan), _labels(new std::list<QLabel *>), _items(new std::list<ItemView *>), _last(NULL),
  _changed(true)
{
  ui.setupUi(this);
  // ui.addWidget(new ItemView(this, wMan), 50, 50);
  // ItemView *item = new ItemView(this, wMan);
  // item->show();
  // item->move(1, 121);
  // item->resize(50,50);
  // ui.gridLayout->addWidget(new ItemView(this, wMan), 1, 0);
}

StuffView::~StuffView()
{
  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  delete _labels;
  for (auto it = _items->begin() ; it != _items->end() ; it++)
    delete *it;
  delete _items;
}

void	StuffView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				StuffView::setItem(Equipment const *equipment, Stuff::eStuff stuff, int x, int y)
{
  ItemView			*item;

  if (equipment->stuffExists(stuff))
    {
      item = new ItemView(this, _wMan, 0, &(equipment->getStuff(stuff)));
      item->move(x, y);
      item->resize(120, 80);
      item->show();
      _items->push_back(item);
    }
}

void				StuffView::setEquipment(Equipment const *equipment)
{
  for (auto it = _items->begin() ; it != _items->end() ; it++)
    delete *it;
  _items->clear();
  setItem(equipment, Stuff::HELMET, 0, 70);
  setItem(equipment, Stuff::SHOULDERS, 0, 170);
  setItem(equipment, Stuff::BREASTPLATE, 0, 270);
  setItem(equipment, Stuff::CLOAK, 0, 370);
  setItem(equipment, Stuff::BOOTS, 0, 470);
  setItem(equipment, Stuff::NECKLACE, 380, 70);
  setItem(equipment, Stuff::RING, 380, 170);
  setItem(equipment, Stuff::WEAPON, 380, 270);
}

void				StuffView::initStuff(Player const &player)
{
  if (_last == &player && !_changed)
    return;
  bool				visible = isVisible();
  _last = &player;
  _changed = false;
  ui.l_name->setText(player.getName().c_str());
  ui.l_faction->setText(player.getFaction().getName().c_str());
  ui.l_guilde->setText("NO GUILDE");
  ui.l_level->setText(std::to_string(player.getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(player.getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(player.getExp()).c_str());

  Equipment const		*equipment = &player.getEquipment();

  setEquipment(equipment);
  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  _labels->clear();
  unsigned int			i = 0;
  for (auto it = player.getStats().begin() ; it != player.getStats().end() ; it ++)
    {
      QLabel			*label = new QLabel(this);
      label->setText((*it)->getKey().getName().c_str());
      label->move(520, 170 + i * 40);
      label->show();
      _labels->push_back(label);
      label = new QLabel(this);
      label->setText(std::to_string((*it)->getValue()).c_str());
      label->move(710, 170 + i * 40);
      label->show();
      _labels->push_back(label);
      i++;
    }
  if (visible)
    _wMan->getSFMLView()->displayView(this);
}

void				StuffView::initStuff(Mob const &mob)
{
  if (_last == &mob && !_changed)
    return;
  _last = &mob;
  bool				visible = isVisible();
  Equipment const		*equipment = &mob.getEquipment();

  _changed = false;
  setEquipment(equipment);
  ui.l_name->setText(mob.getName().c_str());
  ui.l_level->setText(std::to_string(mob.getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(mob.getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(mob.getExp()).c_str());
  unsigned int			i = 0;
  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  _labels->clear();
  for (auto it = mob.getStats().begin() ; it != mob.getStats().end() ; it ++)
    {
      QLabel			*label = new QLabel(this);
      label->setText((*it)->getKey().getName().c_str());
      label->move(520, 170 + i * 40);
      _labels->push_back(label);
      label->show();
      label = new QLabel(this);
      label->setText(std::to_string((*it)->getValue()).c_str());
      label->move(710, 170 + i * 40);
      label->show();
      _labels->push_back(label);
      i++;
    }
  if (visible)
    _wMan->getSFMLView()->displayView(this);
}

void				StuffView::itemAction(ItemView *item)
{
  Stuff const			*stuff = static_cast<Stuff const *>(&item->getItem());

  bool			ret;

  if (_last->getCharacterType() == ACharacter::MOB)
    ret = (**(_wMan->getMainPlayer()))->getMobEquipment(_last->getId(), stuff->getId());
  else
    ret = (**(_wMan->getMainPlayer()))->getPlayerEquipment(stuff->getId());

  if (ret)
    {
      Client::getInstance()->stuff(eStuffAction::GET, stuff->getId(), _last->getId());
      _wMan->getSFMLView()->getInventoryView()->initInventory();
      _changed = true;
      if (_last->getCharacterType() == ACharacter::MOB)
	initStuff(*static_cast<Mob const *>(_last));
      else
	initStuff(*static_cast<Player const *>(_last));
    }
}

ACharacter const		*StuffView::getLast() const { return (_last); }

void				StuffView::setChanged(bool changed) { _changed = changed; }

void				StuffView::dragMoveEvent(QDragMoveEvent *de)
{
  de->accept();
}
 
void				StuffView::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}

void				StuffView::dropEvent(QDropEvent *de)
{
  std::pair<AItem const *, unsigned int>	*pair =
    reinterpret_cast<std::pair<AItem const *, unsigned int> *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

  if (pair->first->getItemType() == AItem::STUFF)
    {
      Stuff const		*stuff = static_cast<Stuff const *>(pair->first);
      bool			ret;

      if (_last->getCharacterType() == ACharacter::MOB)
	ret = (**(_wMan->getMainPlayer()))->putMobEquipment(_last->getId(), stuff->getId());
      else
	ret = (**(_wMan->getMainPlayer()))->putPlayerEquipment(stuff->getId());
      if (ret)
	{
	  Client::getInstance()->stuff(eStuffAction::PUT, stuff->getId(), _last->getId());
	  _changed = true;
	  if (_last->getCharacterType() == ACharacter::MOB)
	    initStuff(*static_cast<Mob const *>(_last));
	  else
	    initStuff(*static_cast<Player const *>(_last));
	  _wMan->getSFMLView()->getInventoryView()->initInventory();
	}
    }
  //   {

  //     itemAction(new ItemView(this, _wMan, 0, pair->first));
  //   }
}

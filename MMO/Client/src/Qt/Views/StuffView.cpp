//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Thu Mar 20 23:09:40 2014 alexis mestag
//

#include			<iostream>
#include			<QMessageBox>
#include			"Qt/Views/StuffView.hh"
#include			"Client.hh"

StuffView::StuffView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan), _labels(new std::list<QLabel *>), _stacks(new std::list<StackView *>), _last(NULL),
  _changed(true)
{
  ui.setupUi(this);
  // ui.addWidget(new StackView(this, wMan), 50, 50);
  // StackView *stack = new StackView(this, wMan);
  // stack->show();
  // stack->move(1, 121);
  // stack->resize(50,50);
  // ui.gridLayout->addWidget(new StackView(this, wMan), 1, 0);
}

StuffView::~StuffView()
{
  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  delete _labels;
  for (auto it = _stacks->begin() ; it != _stacks->end() ; it++)
    delete *it;
  delete _stacks;
}

void	StuffView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				StuffView::setStack(Equipment const *equipment, Stuff::eStuff stuff, int x, int y)
{
  StackView			*stack;

  if (equipment->stuffExists(stuff))
    {
      stack = new StackView(this, _wMan,
			    new Stack<AItem>(equipment->getStuff(stuff).getId(), const_cast<Stuff *>(&equipment->getStuff(stuff)), 0));
      stack->move(x, y);
      stack->resize(62, 58);
      stack->show();
      _stacks->push_back(stack);
    }
}

void				StuffView::setEquipment(Equipment const *equipment)
{
  for (auto it = _stacks->begin() ; it != _stacks->end() ; it++)
    delete *it;
  _stacks->clear();
  setStack(equipment, Stuff::HELMET, 67, 127);
  setStack(equipment, Stuff::NECKLACE, 67, 214);
  setStack(equipment, Stuff::CLOAK, 67, 301);
  setStack(equipment, Stuff::RING, 67, 387);
  setStack(equipment, Stuff::SHOULDERS, 326, 127);
  setStack(equipment, Stuff::BREASTPLATE, 326, 214);
  setStack(equipment, Stuff::WEAPON, 326, 301);
  setStack(equipment, Stuff::BOOTS, 326, 387);
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
  ui.l_guilde->setText((player.getGuild() == NULL ? "" : player.getGuild()->getName().c_str()));
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
      QLabel			*label = new QLabel(ui.f_stats);
      label->setText(it->getKey().getName().c_str());
      label->move(10, 130 + i * 40);
      label->resize(120, 20);
      label->show();
      _labels->push_back(label);
      label = new QLabel(ui.f_stats);
      label->setText(std::to_string(it->getValue()).c_str()); 
      label->move(180, 130 + i * 40);
      label->resize(80, 20);
      label->show();
      label->setAlignment(Qt::AlignRight);
      _labels->push_back(label);
      i++;
    }
  ui.f_stats->resize(270, 130 + i * 40);
  // for (auto it = player.getStats().begin() ; it != player.getStats().end() ; it ++)
  //   {
  //     QLabel			*label = new QLabel(this);
  //     label->setText((*it)->getKey().getName().c_str());
  //     label->move(520, 170 + i * 40);
  //     label->show();
  //     _labels->push_back(label);
  //     label = new QLabel(this);
  //     label->setText(std::to_string((*it)->getValue()).c_str());
  //     label->move(710, 170 + i * 40);
  //     label->show();
  //     _labels->push_back(label);
  //     i++;
  //   }
  if (visible)
    _wMan->getSFMLView()->displayView(this);
}

void				StuffView::initStuff(Mob const &mob)
{
  if (_last == &mob && !_changed)
    return;
  _last = &mob;
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
  for (auto it = mob.getAuthorizedStatKeys().begin() ; it != mob.getAuthorizedStatKeys().end() ; it ++)
    {
      QLabel			*label = new QLabel(ui.f_stats);
      label->setText((*it)->getName().c_str());
      label->move(10, 130 + i * 40);
      label->resize(120, 20);
      _labels->push_back(label);
      label->show();
      label = new QLabel(ui.f_stats);
      label->setText(std::to_string(mob.getCurrentStat((*it)->getName())).c_str());
      label->move(180, 130 + i * 40);
      label->resize(80, 20);
      label->show();
      label->setAlignment(Qt::AlignRight);
      _labels->push_back(label);
      i++;
    }
  ui.f_stats->resize(270, 130 + i * 40);

  // for (auto it = mob.getAuthorizedStatKeys().begin() ; it != mob.getAuthorizedStatKeys().end() ; it ++)
  //   {
  //     QLabel			*label = new QLabel(this);
  //     label->setText((*it)->getName().c_str());
  //     label->move(520, 170 + i * 40);
  //     _labels->push_back(label);
  //     label->show();
  //     label = new QLabel(this);
  //     label->setText(std::to_string(mob.getCurrentStat((*it)->getName())).c_str());
  //     label->move(710, 170 + i * 40);
  //     label->show();
  //     _labels->push_back(label);
  //     i++;
  //   }
  _wMan->getSFMLView()->displayView(this);
}

void				StuffView::stackAction(StackView *stack)
{
  Stuff const			*stuff = static_cast<Stuff const *>(stack->getStack().getItem());

  bool			ret;

  if (_last->getCharacterType() == ACharacter::MOB)
    ret = (**(_wMan->getMainPlayer()))->getMobEquipment(_last->getId(), stuff->getId());
  else
    ret = (**(_wMan->getMainPlayer()))->getPlayerEquipment(stuff->getId());

  if (ret)
    {
      Client::getInstance()->getStuff(stuff->getId(), _last->getId());
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
  Stack<AItem> const		*stack = reinterpret_cast<Stack<AItem> const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

  if (stack->getItem()->getItemType() == AItem::STUFF)
    {
      bool			ret;

      if (_last->getCharacterType() == ACharacter::MOB)
	ret = (**(_wMan->getMainPlayer()))->putMobEquipment(_last->getId(), stack->getId());
      else
	ret = (**(_wMan->getMainPlayer()))->putPlayerEquipment(stack->getId());
      if (ret)
	{
	  Client::getInstance()->putStuff(stack->getId(), _last->getId());
	  _changed = true;
	  if (_last->getCharacterType() == ACharacter::MOB)
	    initStuff(*static_cast<Mob const *>(_last));
	  else
	    initStuff(*static_cast<Player const *>(_last));
	  _wMan->getSFMLView()->getInventoryView()->initInventory();
	}
    }
  //   {

  //     stackAction(new StackView(this, _wMan, 0, pair->first));
  //   }
}

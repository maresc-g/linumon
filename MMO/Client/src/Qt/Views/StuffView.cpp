//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Tue Mar  4 11:08:14 2014 guillaume marescaux
//

#include			<iostream>
#include			<QMessageBox>
#include			"Qt/Views/StuffView.hh"
#include			"Client.hh"

StuffView::StuffView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan), _labels(new std::list<QLabel *>), _items(new std::list<ItemView *>), _last(NULL)
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
      item = new ItemView(this, _wMan, 0, new Stuff(equipment->getStuff(stuff)));
      item->move(x, y);
      item->resize(120, 80);
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
  if (_last == &player)
    return;
  _last = &player;
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
  for (auto it = player.getStats().getStats().begin() ; it != player.getStats().getStats().end() ; it ++)
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
  show();
}

void				StuffView::initStuff(Mob const &mob)
{
  if (_last == &mob)
    return;
  _last = &mob;
  Equipment const		*equipment = &mob.getEquipment();

  setEquipment(equipment);
  ui.l_name->setText(mob.getName().c_str());
  ui.l_level->setText(std::to_string(mob.getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(mob.getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(mob.getExp()).c_str());
  unsigned int			i = 0;
  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  _labels->clear();
  for (auto it = mob.getStats().getStats().begin() ; it != mob.getStats().getStats().end() ; it ++)
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
  show();
}

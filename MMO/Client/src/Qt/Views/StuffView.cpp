//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Tue Feb 25 14:29:10 2014 guillaume marescaux
//

#include			<iostream>
#include			<QMessageBox>
#include			"Qt/Views/StuffView.hh"
#include			"Client.hh"

StuffView::StuffView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan)
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
}

void	StuffView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				StuffView::initStuff(Player const &player)
{
  ui.l_name->setText(player.getName().c_str());
  ui.l_faction->setText(player.getFaction().getName().c_str());
  ui.l_guilde->setText("NO GUILDE");
  ui.l_level->setText(std::to_string(player.getLevel().getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(player.getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(player.getLevel().getExp()).c_str());

  Equipment const		*equipment = &player.getEquipment();
  ItemView			*item;

  if (equipment->stuffExists(Stuff::HELMET))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::HELMET)));
      item->move(0, 70);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::SHOULDERS))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::SHOULDERS)));
      item->move(0, 170);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::BREASTPLATE))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::BREASTPLATE)));
      item->move(0, 270);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::CLOAK))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::CLOAK)));
      item->move(0, 370);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::BOOTS))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::BOOTS)));
      item->move(0, 470);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::NECKLACE))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::NECKLACE)));
      item->move(380, 70);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::RING))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::RING)));
      item->move(380, 170);
      item->resize(120, 80);
    }
  if (equipment->stuffExists(Stuff::WEAPON))
    {
      item = new ItemView(this, _wMan, new Stuff(equipment->getStuff(Stuff::WEAPON)));
      item->move(380, 270);
      item->resize(120, 80);
    }

  unsigned int			i = 0;
  for (auto it = player.getStats().getStats().begin() ; it != player.getStats().getStats().end() ; it ++)
    {
      QLabel			*label = new QLabel(this);
      label->setText((*it)->getKey().getName().c_str());
      label->move(520, 160 + i * 30);
      label = new QLabel(this);
      label->setText(std::to_string((*it)->getValue()).c_str());
      label->move(710, 160 + i * 30);
      i++;
    }
}

void				StuffView::initStuff(Mob const &mob)
{
  ui.l_name->setText(mob.getName().c_str());
  ui.l_level->setText(std::to_string(mob.getLevel().getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(mob.getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(mob.getLevel().getExp()).c_str());
  unsigned int			i = 0;
  for (auto it = mob.getStats().getStats().begin() ; it != mob.getStats().getStats().end() ; it ++)
    {
      QLabel			*label = new QLabel(this);
      label->setText((*it)->getKey().getName().c_str());
      label->move(520, 160 + i * 30);
      label = new QLabel(this);
      label->setText(std::to_string((*it)->getValue()).c_str());
      label->move(710, 160 + i * 30);
      i++;
    }
}

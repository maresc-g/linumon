//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Fri Feb 21 14:18:15 2014 guillaume marescaux
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

void				StuffView::initStuff()
{
  MutexVar<Player *>		*player = _wMan->getMainPlayer();
  Digitaliser const		*digitaliser = &(**player)->getDigitaliser();
  std::list<Mob *> const	mobs = digitaliser->getMobs();
  Mob				*mob = mobs.back();

  std::cout << "LIST SIIIIIIIIIIIIZE = " << mobs.size() << std::endl;
  // ui.l_name->setText((**player)->getName().c_str());
  // ui.l_faction->setText((**player)->getFaction().getName().c_str());
  // ui.l_guilde->setText("NO GUILDE");
  // ui.l_level->setText(std::to_string((**player)->getLevel().getLevel()).c_str());
  // ui.l_curExp->setText(std::to_string((**player)->getCurrentExp()).c_str());
  // ui.l_expToUp->setText(std::to_string((**player)->getLevel().getExp()).c_str());

  ui.l_name->setText(mob->getName().c_str());
  ui.l_level->setText(std::to_string(mob->getLevel().getLevel()).c_str());
  ui.l_curExp->setText(std::to_string(mob->getCurrentExp()).c_str());
  ui.l_expToUp->setText(std::to_string(mob->getLevel().getExp()).c_str());
  int i = 0;
  auto it = (&(mob->getModel()))->getStats();
  for (auto it = mob->getModel().getStats().getStats().begin() ; it != mob->getModel().getStats().getStats().end() ; it ++)
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

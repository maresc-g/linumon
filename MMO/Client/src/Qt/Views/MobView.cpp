//
// MobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:44:59 2014 guillaume marescaux
// Last update Fri Feb 28 15:53:46 2014 guillaume marescaux
//

#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/MobView.hh"

MobView::MobView(QWidget *parent, WindowManager *wMan, unsigned int nb, Mob *mob):
  QWidget(parent), _wMan(wMan), _mob(mob), _nb(nb)
{
  ui.setupUi(this);
  if (nb > 0)
    {
      ui.l_nb->setText(std::to_string(nb).c_str());
      ui.l_nb->move(ITEM_SIZE - 20, ITEM_SIZE - 20);
      ui.l_nb->show();
    }
  else
    ui.l_nb->hide();
  std::string name = mob->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  std::cout << "NAME = " << name << std::endl;
  this->setStyleSheet(std::string("MobView QFrame#" + name + "{ border-image: url(./Res/Mobs/" + name + ".png); }").c_str());
}

MobView::MobView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _mob(NULL), _nb(0)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  this->setObjectName("default");
  // this->setStyleSheet("MobView#default { border-image: url(./Res/Mobs/bottes_bouftou.png); }");
}

MobView::~MobView()
{
}

void				MobView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//
// HUDView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar  6 13:10:17 2014 guillaume marescaux
// Last update Thu Mar  6 15:34:37 2014 guillaume marescaux
//

#include			"Qt/Views/HUDView.hh"

# define			GREEN "#33C71F"
# define			ORANGE "#E77E18"
# define			RED "#E72518"

HUDView::HUDView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _mobView(new MobView(this, wMan))
{
  ui.setupUi(this);
  _mobView->move(10, 10);
  _mobView->resize(100, 100);
}

HUDView::~HUDView()
{
}

void				HUDView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				HUDView::setInfos(Mob const *mob)
{
  _mobView->setInfos(mob);
  if (mob)
    {
      unsigned int		current = mob->getTmpStat("HP");
      unsigned int		max = mob->getStat("HP");
      ui.pb_hp->setMaximum(max);
      ui.pb_hp->setValue(current);
      if (current / max * 100 <= 20)
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(RED) + "; }").c_str());
      else if (current / max * 100 <= 50)
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(ORANGE) + "; }").c_str());
      else
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(GREEN) + "; }").c_str());
      ui.pb_exp->setMaximum(mob->getExp());
      ui.pb_exp->setValue(mob->getCurrentExp());
      ui.l_name->setText(mob->getName().c_str());
      ui.l_lvl->setText(std::to_string(mob->getLevel()).c_str());
    }
}

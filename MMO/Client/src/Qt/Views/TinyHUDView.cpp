//
// TinyHUDView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar  6 14:21:30 2014 guillaume marescaux
// Last update Tue Mar 25 16:54:03 2014 guillaume marescaux
//

#include			"Qt/Views/TinyHUDView.hh"

# define			GREEN "#33C71F"
# define			ORANGE "#E77E18"
# define			RED "#E72518"

TinyHUDView::TinyHUDView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _mobView(new MobView(this, wMan))
{
  ui.setupUi(this);
  _mobView->move(5, 5);
  _mobView->resize(50, 50);
  this->resize(90, 100);
  ui.pb_hp->move(5, 60);
  ui.pb_hp->resize(80, 15);
  ui.pb_exp->resize(80, 10);
  ui.pb_exp->move(5, 85);
  ui.l_hp->move(5, 60);
  ui.l_hp->resize(80, 15);
  ui.l_exp->resize(80, 10);
  ui.l_exp->move(5, 85);
  ui.pb_exp->setTextVisible(false);
  ui.pb_hp->setTextVisible(false);
  ui.l_lvl->move(70, 5);
  ui.l_name->hide();
  ui.l_level->hide();
}

TinyHUDView::~TinyHUDView()
{
}

void				TinyHUDView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				TinyHUDView::setInfos(Mob const *mob)
{
  _mobView->setInfos(mob);
  if (mob)
    {
      double			current = mob->getCurrentStat("HP");
      unsigned int		max = mob->getMaxStat("HP");

      ui.pb_hp->setMaximum(max);
      ui.pb_hp->setValue(current);
      if ((double)(current / max) * 100 <= 20)
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(RED) + "; }").c_str());
      else if ((double)(current / max) * 100 <= 50)
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(ORANGE) + "; }").c_str());
      else
      	ui.pb_hp->setStyleSheet(std::string("QProgressBar::chunk { background-color: " + std::string(GREEN) + "; }").c_str());
      ui.l_exp->setText(std::string("EXP : " + std::to_string(mob->getCurrentExp()) + "/" + std::to_string(mob->getExp())).c_str());
      ui.l_hp->setText(std::string("HP : " + std::to_string((int)current) + "/" + std::to_string(max)).c_str());
      ui.pb_exp->setMinimum(mob->getOldExp());
      ui.pb_exp->setMaximum(mob->getExp());
      ui.pb_exp->setValue(mob->getCurrentExp());
      ui.l_lvl->setText(std::to_string(mob->getLevel()).c_str());
    }
}

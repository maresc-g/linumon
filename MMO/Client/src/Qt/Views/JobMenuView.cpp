//
// JobMenuView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 12:56:12 2014 guillaume marescaux
// Last update Thu Mar  6 12:15:01 2014 guillaume marescaux
//

#include			"SFML/SFMLView.hpp"
#include			"Qt/Views/JobMenuView.hh"

JobMenuView::JobMenuView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

JobMenuView::~JobMenuView()
{
}

void				JobMenuView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				JobMenuView::initJob(std::string const &name)
{
  SFMLView		*sfml = static_cast<SFMLView *>(this->parentWidget());
  JobView		*job = sfml->getJobView();

  job->setInfos(*(**(_wMan)->getMainPlayer())->getJob(name));
  job->move(300, 100);
  _wMan->getSFMLView()->displayView(job);
}

void				JobMenuView::on_b_alch_clicked()
{
  initJob("Maitre des Potions");
}

void				JobMenuView::on_b_dev_clicked()
{
  initJob("Developpeur");
}

void				JobMenuView::on_b_armu_clicked()
{
  initJob("Armurier");
}

void				JobMenuView::on_b_inge_clicked()
{
  initJob("Ingenieur");
}

void				JobMenuView::on_b_miner_clicked()
{
  initJob("Mineur");
}

void				JobMenuView::on_b_trapper_clicked()
{
  initJob("Trappeur");
}

void				JobMenuView::on_b_herbo_clicked()
{
  initJob("Herboriste");
}

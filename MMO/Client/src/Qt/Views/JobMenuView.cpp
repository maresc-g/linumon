//
// JobMenuView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 12:56:12 2014 guillaume marescaux
// Last update Thu Feb 27 13:12:30 2014 guillaume marescaux
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
  job->show();
}

void				JobMenuView::on_b_alch_clicked()
{
  initJob("Maitre des potions");
}

void				JobMenuView::on_b_dev_clicked()
{
  initJob("Développeur");
}

void				JobMenuView::on_b_crafter1_clicked()
{
  initJob("Armurier");
}

void				JobMenuView::on_b_crafter2_clicked()
{
  initJob("Ingénieur");
}

void				JobMenuView::on_b_mineur_clicked()
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

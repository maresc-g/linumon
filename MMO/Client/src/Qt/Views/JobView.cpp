//
// JobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:55:36 2014 guillaume marescaux
// Last update Tue Feb 25 16:26:55 2014 guillaume marescaux
//

#include			"Qt/Views/JobView.hh"

JobView::JobView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

JobView::~JobView()
{
}

void				JobView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				JobView::setInfos(Job const &job)
{
  ui.l_name->setText(job.getJobModel().getName().c_str());
}

void				JobView::on_b_craft_clicked()
{
}

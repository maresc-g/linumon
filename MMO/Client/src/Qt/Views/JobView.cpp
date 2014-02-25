//
// JobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:55:36 2014 guillaume marescaux
// Last update Tue Feb 25 14:55:51 2014 guillaume marescaux
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

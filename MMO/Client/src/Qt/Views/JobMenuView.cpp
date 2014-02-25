//
// JobMenuView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 12:56:12 2014 guillaume marescaux
// Last update Tue Feb 25 12:58:15 2014 guillaume marescaux
//

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

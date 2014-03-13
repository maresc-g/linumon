//
// SplitStackView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:59:24 2014 guillaume marescaux
// Last update Wed Mar 12 14:09:43 2014 guillaume marescaux
//

#include			"Qt/Views/SplitStackView.hh"

SplitStackView::SplitStackView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

SplitStackView::~SplitStackView()
{
}

void				SplitStackView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				SplitStackView::on_b_accept_clicked()
{
}

void				SplitStackView::on_b_cancel_clicked()
{
}

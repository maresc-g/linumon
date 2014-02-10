//
// ItemView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Mon Feb 10 13:17:28 2014 cyril jourdain
//

#include			"Qt/Views/ItemView.hh"

ItemView::ItemView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

ItemView::~ItemView()
{
}

void				ItemView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
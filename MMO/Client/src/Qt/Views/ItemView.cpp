//
// ItemView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Tue Feb 11 13:05:23 2014 guillaume marescaux
//

#include			"Qt/Views/ItemView.hh"

ItemView::ItemView(QWidget *parent, WindowManager *wMan, AItem *item):
  QWidget(parent), _wMan(wMan), _item(item)
{
  ui.setupUi(this);
  this->setStyleSheet("QWidget { border-image: url(./Res/test.jpg); }");;
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

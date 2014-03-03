//
// DigitaliserView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:34:08 2014 guillaume marescaux
// Last update Fri Feb 28 15:35:37 2014 guillaume marescaux
//

#include			"Qt/Views/DigitaliserView.hh"

DigitaliserView::DigitaliserView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _scrollArea(new QScrollArea), _frame(new QFrame)
{
  ui.setupUi(this);
  ui.gl_scroll->addWidget(_scrollArea);
  _scrollArea->setObjectName("scrollPerso");
  _frame->setObjectName("scrollPerso");
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrollArea->setWidget(_frame);
  QLabel *label = new QLabel("test", _frame);
  _frame->resize(100, 100);
  label->move(0, 50);
}

DigitaliserView::~DigitaliserView()
{
}

void				DigitaliserView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//
// SwitchMobView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 13 14:44:54 2014 cyril jourdain

//

#include			"Qt/Views/SwitchMobView.hh"
#include			<QPainter>

SwitchMobView::SwitchMobView(QWidget *parent, Digitaliser const &digit) :
  QDialog(parent), _scrollArea(new QScrollArea()), _frame(new QFrame())
{
  ui.setupUi(this);
  ui.layout->addWidget(_scrollArea);
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrollArea->setWidget(_frame);
}

SwitchMobView::~SwitchMobView()
{
}

void				SwitchMobView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				SwitchMobView::accept()
{
  setResult(15);
}

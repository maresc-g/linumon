//
// SwitchMobView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 13 14:44:54 2014 cyril jourdain

//

#include			<QPainter>
#include			"Qt/Views/MobView.hh"
#include			"Qt/Views/SwitchMobView.hh"
#include <QDebug>

SwitchMobView::SwitchMobView(QWidget *parent, Digitaliser::Mobs const *mobs, WindowManager *wMan) :
  QDialog(parent), _scrollArea(new QScrollArea()), _frame(new QFrame())
{
  MobView			*mobView = NULL;
  int				i = 0;

  setWindowFlags(Qt::Widget);
  ui.setupUi(this);
  ui.layout->addWidget(_scrollArea);
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrollArea->setWidget(_frame);
  connect(ui.b_cancel, SIGNAL(clicked()), this, SLOT(accept()));
  for (auto it = mobs->begin() ; it != mobs->end() ; it++)
    {
      mobView = new MobView(_frame, wMan, *it);
      mobView->move(i % 6 * 81,0);
      mobView->resize(80, 80);
      mobView->show();
      connect(mobView, SIGNAL(clicked(unsigned int)), this, SLOT(selectMob(unsigned int)));
      //_mobs->push_back(mobView);
      i++;
    }
  _frame->resize(486, 80);
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

void				SwitchMobView::selectMob(unsigned int id)
{
  done(id);
}

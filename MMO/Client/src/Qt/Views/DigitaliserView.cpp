//
// DigitaliserView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:34:08 2014 guillaume marescaux
// Last update Thu Mar  6 13:28:21 2014 guillaume marescaux
//

#include			"Qt/Views/DigitaliserView.hh"
#include			"Entities/Digitaliser.hh"

DigitaliserView::DigitaliserView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _scrollArea(new QScrollArea), _frame(new QFrame),
  _mobs(new std::list<MobView *>), _battleMobs(new std::list<MobView *>)
{
  ui.setupUi(this);
  ui.gl_scroll->addWidget(_scrollArea);
  _scrollArea->setObjectName("scrollPerso");
  _frame->setObjectName("scrollPerso");
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrollArea->setWidget(_frame);
  _frame->resize(200, 500);
}

DigitaliserView::~DigitaliserView()
{
  for (auto it = _mobs->begin() ; it != _mobs->end() ; it++)
    delete *it;
  for (auto it = _battleMobs->begin() ; it != _battleMobs->end() ; it++)
    delete *it;
  delete _mobs;
  delete _battleMobs;
}

void				DigitaliserView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				DigitaliserView::initDigit(Digitaliser const &digit)
{
  Digitaliser::Mobs const	mobs = digit.getMobs();
  MobView			*mobView;
  int				i = 0;

  for (auto it = mobs.begin() ; it != mobs.end() ; it++)
    {
      mobView = new MobView(ui.f_battleMobs, _wMan, *it);
      mobView->move(i * 80 + i, 0);
      mobView->resize(80, 80);
      mobView->show();
      _mobs->push_back(mobView);
      i++;
    }
}

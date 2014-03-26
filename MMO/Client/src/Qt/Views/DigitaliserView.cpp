//
// DigitaliserView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 14:34:08 2014 guillaume marescaux
// Last update Tue Mar 25 20:20:38 2014 guillaume marescaux
//

#include			"Qt/Views/DigitaliserView.hh"
#include			"Entities/Digitaliser.hh"

DigitaliserView::DigitaliserView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _scrollArea(new QScrollArea), _f_battleMobs(new FrameMobs(this,wMan)),
  _frame(new FrameMobs(this, wMan)), _mobs(new std::list<MobView *>), _battleMobs(new std::list<MobView *>),
  _hiddenMobs(new std::list<MobView *>), _hiddenBattleMobs(new std::list<MobView *>)
{
  ui.setupUi(this);
  std::cout << "SIZE X = " << this->size().width() << std::endl;
  ui.gl_scroll->addWidget(_scrollArea);
  _scrollArea->setObjectName("scrollArea");
  _frame->setObjectName("scrollPerso");
  _f_battleMobs->setObjectName("f_battleMobs");
  _f_battleMobs->resize(486, 80);
  _f_battleMobs->move(120, 10);
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrollArea->setWidget(_frame);
  QLabel			*label = new QLabel(_frame);

  label->setText("DROP HERE");
  label->move(180, 20);
}

DigitaliserView::~DigitaliserView()
{
  for (auto it = _mobs->begin() ; it != _mobs->end() ; it++)
    delete *it;
  for (auto it = _battleMobs->begin() ; it != _battleMobs->end() ; it++)
    delete *it;
  for (auto it = _hiddenMobs->begin() ; it != _hiddenMobs->end() ; it++)
    delete *it;
  for (auto it = _hiddenBattleMobs->begin() ; it != _hiddenBattleMobs->end() ; it++)
    delete *it;
  delete _mobs;
  delete _battleMobs;
  delete _hiddenMobs;
  delete _hiddenBattleMobs;
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
  Digitaliser::Mobs		mobs = digit.getBattleMobs();
  MobView			*mobView;
  int				i = 0;

  for (auto it = _hiddenMobs->begin() ; it != _hiddenMobs->end() ; it++)
    delete *it;
  _hiddenMobs->clear();
  for (auto it = _mobs->begin() ; it != _mobs->end() ; it++)
    {
      (*it)->hide();
      _hiddenMobs->push_back(*it);
    }
  _mobs->clear();
  for (auto it = _hiddenBattleMobs->begin() ; it != _hiddenBattleMobs->end() ; it++)
    delete *it;
  _hiddenBattleMobs->clear();
  for (auto it = _battleMobs->begin() ; it != _battleMobs->end() ; it++)
    {
      (*it)->hide();
      _hiddenBattleMobs->push_back(*it);
    }
  _battleMobs->clear();
  for (auto it = mobs.begin() ; it != mobs.end() ; it++)
    {
      mobView = new MobView(_f_battleMobs, _wMan, *it);
      mobView->move(i * 80 + i, 0);
      mobView->resize(80, 80);
      mobView->show();
      _mobs->push_back(mobView);
      i++;
    }
  i = 0;
  mobs = digit.getMobs();
  for (auto it = mobs.begin() ; it != mobs.end() ; it++)
    {
      mobView = new MobView(_frame, _wMan, *it);
      mobView->move(i % 6 * 81, i / 6 * 80 + 80);
      mobView->resize(80, 80);
      mobView->show();
      _mobs->push_back(mobView);
      i++;
    }
  std::cout << " ; y = " << i / 5 << std::endl;
  _frame->resize(486, ((i - 1) / 6 + 1) * 80 + 80);
}

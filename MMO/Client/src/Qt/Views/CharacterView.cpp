//
// CharacterView.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 13:05:10 2013 cyril jourdain
// Last update Wed Mar 12 13:58:28 2014 cyril jourdain
//

#include		"Qt/Views/CharacterView.hh"
#include		<iostream>
#include		<unistd.h>
#include		<QMessageBox>
#include		<QLayoutItem>

CharacterView::CharacterView(QWidget *parent, WindowManager *man) :
  QWidget(parent), _wMan(man),
  _charList(new std::vector<CharDescription *>),
  _prev(new QPushButton(this)), _next(new QPushButton(this)),
  _scrollArea(new QScrollArea), _charContainer(new QFrame(this)),
  _charLayout(new QHBoxLayout), _createCharView(new CreateCharView(this, man)),
  _charNumber(0)
{
  ui.setupUi(this);
  _prev->setObjectName("b_prev");
  _next->setObjectName("b_next");
  _createCharView->setObjectName("createCharView");
  _charContainer->setObjectName("charContainer");

  // _widgetLayout->itemAt(_widgetLayout->indexOf(_prev))->setGeometry(QRect(35, 500, 64, 64));

  ui.layoutScroll->addWidget(_scrollArea);
  _scrollArea->setObjectName("scrollPerso");
  _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  _charContainer->setLayout(_charLayout);

  _prev->move(35, 500);
  _next->move(435, 500);
  _prev->resize(64, 64);
  _next->resize(64, 64);

  connect(_prev, SIGNAL(clicked()), this, SLOT(b_prev_clicked()));
  connect(_next, SIGNAL(clicked()), this, SLOT(b_next_clicked()));
  _scrollArea->setWidget(_charContainer);
  _createCharView->move(WIN_W / 2 - _createCharView->size().width() / 2, WIN_H / 2 - _createCharView->size().height() / 2);
  _createCharView->hide();
}

CharacterView::~CharacterView()
{
  delete _prev;
  delete _next;
  delete _charContainer;
  delete _createCharView;
  delete _scrollArea;
  // delete _charLayout;
}

void		CharacterView::clear()
{
  for (auto it = _charList->begin() ; it != _charList->end() ; it++)
    delete *it;
  _charList->clear();
  QLayoutItem *item;
  while ((item = _charLayout->takeAt(0)))
    {
      delete item->widget();
      delete item;
    }
}

void		CharacterView::setPlayers(std::list<PlayerView *> const &players)
{ 
  for (auto it = players.begin() ; it != players.end() ; it++)
    _charList->push_back(new CharDescription(this, **it));
  _charContainer->resize((*_charList)[0]->size().width() * _charList->size(),412);
  _scrollArea->setMaximumSize((*_charList)[0]->size().width(), 412);

  for (auto it = _charList->begin(); it != _charList->end(); it++)
    {
      _charLayout->addWidget(*it);
    }
}

void		CharacterView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void		CharacterView::b_next_clicked()
{
  if (_charList->size() > 0)
    {
      float oldy = (*_charList)[0]->pos().y();
      float oldx;
      int move = (*_charList)[0]->size().width();
      float offset = ((*_charList)[0]->size().width()) / 10.0;

      if (_charNumber < _charList->size() - 1)
	{
	  while (move >= 0)
	    {
	      move -= offset;
	      oldx = _charContainer->pos().x();
	      _charContainer->move(oldx - offset, oldy);
	      repaint();
	    }
	  _charNumber++;
	  _charContainer->move(-(_charContainer->pos().x() + ((*_charList)[_charNumber]->pos().x() - _charContainer->pos().x())), oldy);
	  std::cout << _charNumber << std::endl;
	}
    }
}

void		CharacterView::b_prev_clicked()
{

  if (_charList->size() > 0)
    {
      float oldy = (*_charList)[0]->pos().y();
      float oldx;
      int move = (*_charList)[0]->size().width();
      float offset = ((*_charList)[0]->size().width()) / 10.0;

      if (_charNumber > 0)
	{
	  while (move >= 0)
	    {
	      move -= offset;
	      oldx = _charContainer->pos().x();
	      _charContainer->move(oldx + offset, oldy);
	      repaint();
	    }
	  _charNumber--;
	  _charContainer->move(-(_charContainer->pos().x() + ((*_charList)[_charNumber]->pos().x() - _charContainer->pos().x())), oldy);
	  std::cout << _charNumber << std::endl;
	}
    }
}

void		CharacterView::on_b_back_clicked()
{
  _wMan->hideCharacter();
  _wMan->showLogin();
}

void		CharacterView::on_b_new_clicked()
{
  _createCharView->show();
}

void		CharacterView::on_b_play_clicked()
{
  if (_charList->size() > 0)
    {
      Client::getInstance()->choosePlayer((*_charList)[_charNumber]->getPlayer());
      while (**(_wMan->getState()) == CLIENT::CHOOSE_PLAYER || **(_wMan->getState()) == CLIENT::LOADING)
	usleep(100);
      if (**(_wMan->getState()) == CLIENT::LOADED) {
	_wMan->hideCharacter();
	_wMan->showSfmlView();
      }
      else
	QMessageBox::information(this, "Error", "Unable to join the game");
    }
  else
    QMessageBox::information(this, "Error", "No player available");
}

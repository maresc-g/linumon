//
// SpellBarView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 15:42:00 2014 guillaume marescaux
// Last update Thu Mar  6 10:45:22 2014 guillaume marescaux
//

#include			"Qt/Views/SpellBarView.hh"

SpellBarView::SpellBarView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _buttons(new std::list<QPushButton *>), _spells(NULL), _mapper(new QSignalMapper)
{
  ui.setupUi(this);
}

SpellBarView::~SpellBarView()
{
  for (auto it = _buttons->begin() ; it != _buttons->end() ; it++)
    delete *it;
  delete _buttons;
}

void				SpellBarView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				SpellBarView::handleClick(QString const &name)
{
  for (auto it = _spells->begin() ; it != _spells->end() ; it++)
    {
      if ((*it)->getName() != name.toStdString())
	{
	  break;
	}
    }
}

void				SpellBarView::setInfos(Spells const &spells)
{
  QPushButton			*button;
  int				i = 0;

  _spells = &spells;
  for (auto it = spells.begin() ; it != spells.end() ; it++)
    {
      button = new QPushButton((*it)->getName().c_str(), this);
      button->resize(100, 100);
      button->move(101 * i, 0);
      button->show();
      button->setObjectName((*it)->getName().c_str());
      _mapper->setMapping(button, (*it)->getName().c_str());
      connect(button, SIGNAL(clicked()), _mapper, SLOT(map()));
      i++;
    }
  connect(_mapper, SIGNAL(mapped(QString const &)), this, SLOT(handleClick(QString const &)));
  this->resize(101 * i, 100);
}

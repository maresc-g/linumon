//
// StuffStatsView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Mar 18 10:54:37 2014 guillaume marescaux
// Last update Thu Mar 20 23:10:33 2014 alexis mestag
//

#include		<iostream>
#include		"Qt/Views/StuffStatsView.hh"

StuffStatsView::StuffStatsView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan), _labels(new std::list<QLabel *>)
{
  ui.setupUi(this);
}

StuffStatsView::~StuffStatsView()
{
}

void			StuffStatsView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void			StuffStatsView::setInfos(AItem const *item)
{
  Stats const		*stats;
  Stuff const		*stuff;
  unsigned int		i = 0;

  for (auto it = _labels->begin() ; it != _labels->end() ; it++)
    delete *it;
  _labels->clear();
  ui.l_name->setText(item->getName().c_str());
  if (item->getItemType() == AItem::STUFF)
    {
      stuff = static_cast<Stuff const *>(item);
      stats = &stuff->getStats();
      for (auto it = stats->begin() ; it != stats->end() ; ++it)
	{
	  QLabel			*label = new QLabel(this);
	  label->setText(it->getKey().getName().c_str());
	  label->move(10, 40 + i * 40);
	  label->resize(60, 20);
	  label->show();
	  _labels->push_back(label);
	  label = new QLabel(this);
	  label->setText(std::to_string(it->getValue()).c_str()); 
	  label->move(70, 40 + i * 40);
	  label->resize(100, 20);
	  label->show();
	  label->setAlignment(Qt::AlignRight);
	  _labels->push_back(label);
	  i++;
	}
    }
  this->resize(210, 40 + i * 40);
}

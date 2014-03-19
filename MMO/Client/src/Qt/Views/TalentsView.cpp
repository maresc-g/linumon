//
// TalentsView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 17 22:32:36 2014 guillaume marescaux
// Last update Mon Mar 17 23:15:04 2014 guillaume marescaux
//

#include		<iostream>
#include		"Qt/Views/TalentsView.hh"
#include <QLabel>

TalentsView::TalentsView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan)
{
  ui.setupUi(this);
}

TalentsView::~TalentsView()
{
}

void			TalentsView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void			TalentsView::initTalents(TalentTree const &tree)
{
  TalentModel const	*first = &tree.getTalent();
  std::list<TalentModel const *>	*current = new std::list<TalentModel const *>;
  std::list<TalentModel const *>	*next = new std::list<TalentModel const *>;
  unsigned int		i = 0;
  unsigned int		j = 0;
  QLabel		*label;

  current->push_back(first);
  while (!current->empty())
    {
      j = 0;
      for (auto itCur = current->begin() ; itCur != current->end() ; ++itCur)
	{
	  std::cout << "I AM PUTING A TALENT" << std::endl;
	  label = new QLabel(this);
	  label->setText("toto");
	  label->move(j * 50, i * 50);
	  std::list<TalentModel *>	sons = (*itCur)->getTalents();
	  for (auto itSons = sons.begin() ; itSons != sons.end() ; ++itSons)
	    {
	      std::cout << "I AM PUTING A SON" << std::endl;
	      next->push_back(*itSons);
	    }
	  j++;
	}
      delete current;
      current = next;
      next = new std::list<TalentModel const *>;
      i++;
    }
  delete next;
}

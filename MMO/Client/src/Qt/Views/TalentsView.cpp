//
// TalentsView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 17 22:32:36 2014 guillaume marescaux
// Last update Wed Mar 19 17:55:12 2014 alexis mestag
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
  std::list<TalentModel const *> const	*current = &tree.getTalents();
  std::list<TalentModel const *>	*next = new std::list<TalentModel const *>;
  unsigned int		i = 0;
  unsigned int		j = 0;
  QLabel		*label;

  std::cerr << "current->size() = " << current->size() << std::endl;
  std::cerr << "tree name = " << tree.getName() << std::endl;
  while (!current->empty())
    {
      j = 0;
      for (auto itCur = current->begin() ; itCur != current->end() ; ++itCur)
	{
	  std::cout << "I AM PUTING A TALENT" << std::endl;
	  label = new QLabel(this);
	  label->setText((*itCur)->getName().c_str());
	  label->move(j * 50, i * 50);
	  std::list<TalentModel const *> const	*sons = &(*itCur)->getTalents();
	  for (auto itSons = sons->begin() ; itSons != sons->end() ; ++itSons)
	    {
	      std::cout << "I AM PUTING A SON" << std::endl;
	      next->push_back(*itSons);
	    }
	  j++;
	}
      // delete current;
      current = next;
      next = new std::list<TalentModel const *>;
      i++;
    }
  // delete next;
}

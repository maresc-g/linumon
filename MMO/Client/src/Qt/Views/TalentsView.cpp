//
// TalentsView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 17 22:32:36 2014 guillaume marescaux
// Last update Thu Mar 20 16:44:37 2014 guillaume marescaux
//

#include		<iostream>
#include		"Qt/Views/TalentsView.hh"
#include		"JsonFile/JsonFile.hh"

TalentsView::TalentsView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan), _talentViews(new std::list<TalentView *>)
{
  ui.setupUi(this);
}

TalentsView::~TalentsView()
{
  for (auto it = _talentViews->begin() ; it != _talentViews->end() ; it++)
    delete *it;
  delete _talentViews;
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
  TalentView				*talent;
  JsonFile				file;

  JsonFile::readFile(file, "Res/TalentCoords.json");
  for (auto it = _talentViews->begin() ; it != _talentViews->end() ; it++)
    delete *it;
  _talentViews->clear();
  current = &tree.getTalents();
  next = new std::list<TalentModel const *>;
  while (!current->empty())
    {
      for (auto itCur = current->begin() ; itCur != current->end() ; ++itCur)
  	{
  	  talent = new TalentView(this, _wMan, (*itCur), (**_wMan->getMainPlayer())->getTalentFromModel(**itCur));
	  talent->move(file[(*itCur)->getName()]["x"].asInt(), file[(*itCur)->getName()]["y"].asInt());
  	  std::list<TalentModel const *> const	*sons = &(*itCur)->getTalents();
  	  for (auto itSons = sons->begin() ; itSons != sons->end() ; ++itSons)
	    next->push_back(*itSons);
  	}
      current = next;
      next = new std::list<TalentModel const *>;
    }
  this->resize(file["size"]["x"].asInt(), file["size"]["y"].asInt());
}

//
// TalentView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar 20 11:02:32 2014 guillaume marescaux
// Last update Fri Mar 21 14:47:15 2014 guillaume marescaux
//

#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/TalentView.hh"

TalentView::TalentView(QWidget *parent, WindowManager *wMan, TalentModel const *talentModel, Talent const *talent):
  QWidget(parent), _wMan(wMan), _talentModel(talentModel), _talent(talent)
{
  ui.setupUi(this);
  setInfos();
  QLabel *label = new QLabel(this);
  label->setText(talentModel->getName().c_str());
}

TalentView::~TalentView()
{
}

void				TalentView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				TalentView::mousePressEvent(QMouseEvent *mEvent)
{
  bool				ret = false;

  if (mEvent->button() == Qt::LeftButton)
    {
      TalentModel const		*parentModel = _talentModel->getParent();

      if (!_talent)
	{
	  Talent const		*parentTalent;

	  if (parentModel)
	    {
	      parentTalent = (**_wMan->getMainPlayer())->getTalentFromModel(*parentModel);
	      if (parentTalent && parentTalent->getCurrentPoints() == parentModel->getMaxPoints())
		ret = true;
	    }
	  else
	    ret = true;
	}
      if (_talent && _talent->getCurrentPoints() < _talentModel->getMaxPoints())
	ret = true;
      if (ret)
	{
	  if ((**_wMan->getMainPlayer())->incTalent(*_talentModel))
	    {
	      _talent = (**_wMan->getMainPlayer())->getTalentFromModel(*_talentModel);
	      setInfos();
	      Client::getInstance()->talents((**_wMan->getMainPlayer())->getTalents());
	    }
	}
    }
}

void				TalentView::setInfos()
{
  if (_talent)
    ui.l_nb->setText(std::to_string(_talent->getCurrentPoints()).c_str());
  else
    ui.l_nb->setText("0");
  ui.l_max->setText(std::to_string(_talentModel->getMaxPoints()).c_str());
  std::string name = _talentModel->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  this->setStyleSheet(std::string("TalentView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());  
}

TalentModel const		*TalentView::getTalentModel() const { return (_talentModel); }
Talent const			*TalentView::getTalent() const { return (_talent); }

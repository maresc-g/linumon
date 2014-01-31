//
// CharDescription.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 15:47:27 2013 cyril jourdain
// Last update Tue Dec 17 13:05:49 2013 cyril jourdain
//

#include		"Qt/CharDescription/CharDescription.hh"

CharDescription::CharDescription(QWidget *parent) :
  QWidget(parent)
{
  ui.setupUi(this);
}

CharDescription::~CharDescription()
{
}

void		CharDescription::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

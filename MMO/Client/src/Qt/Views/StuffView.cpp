//
// StuffView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 14:09:19 2014 guillaume marescaux
// Last update Fri Feb  7 14:09:42 2014 guillaume marescaux
//

#include	<iostream>
#include	<QMessageBox>
#include	"Qt/Views/StuffView.hh"
#include	<unistd.h>
#include	"Client.hh"

StuffView::StuffView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan)
{
  ui.setupUi(this);
}

StuffView::~StuffView()
{
}

void	StuffView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

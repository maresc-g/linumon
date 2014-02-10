//
// ChatView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Feb  6 14:49:44 2014 cyril jourdain

//

#include		<QMessageBox>
#include		"Qt/Views/ChatView.hh"

ChatView::ChatView(QWidget *parent, WindowManager *man) :
  QWidget(parent)
{
  ui.setupUi(this);
}

ChatView::~ChatView()
{
}

void		ChatView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


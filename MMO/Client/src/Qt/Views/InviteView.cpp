//
// InviteView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Mar 21 19:32:53 2014 guillaume marescaux
// Last update Fri Mar 21 19:37:55 2014 guillaume marescaux
//

#include			"Qt/Views/InviteView.hh"

InviteView::InviteView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _name("")
{
  ui.setupUi(this);
}

InviteView::~InviteView()
{
}

void				InviteView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				InviteView::on_b_join_clicked()
{
  Client::getInstance()->acceptGuild(_name);
}

void				InviteView::on_b_decline_clicked()
{
  Client::getInstance()->refuseGuild();
}

void				InviteView::setInfos(std::string const &name)
{
  _name = name;
  ui.l_name->setText(name.c_str());
}

//
// MenuView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb 17 13:30:25 2014 guillaume marescaux
// Last update Tue Feb 18 15:48:37 2014 guillaume marescaux
//

#include			"Qt/Views/MenuView.hh"

MenuView::MenuView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

MenuView::~MenuView()
{
}

void				MenuView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				MenuView::on_bSwitch_clicked()
{
  // Client
}

void				MenuView::on_bLogout_clicked()
{
  std::cout << "TEST" << std::endl;
  Client::getInstance()->disconnect();
}

void				MenuView::on_bQuit_clicked()
{
  qApp->quit();
}

void				MenuView::on_bReturn_clicked()
{
  this->hide();
}

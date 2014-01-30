//
// LoginView.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Oct 18 11:04:31 2013 cyril jourdain
// Last update Thu Jan 30 15:54:43 2014 guillaume marescaux
//

#include	<iostream>
#include	<QMessageBox>
#include	"Qt/LoginView/LoginView.hh"
#include	<unistd.h>
#include	"Client.hh"

LoginView::LoginView(QWidget *parent, WindowManager *wMan) :
  QWidget(parent),  _wMan(wMan)
{
  ui.setupUi(this);
}

LoginView::~LoginView()
{
}

void	LoginView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void	LoginView::on_bConnect_clicked()
{
  if (ui.le_Login->text().isEmpty() || ui.le_Pass->text().isEmpty())
    QMessageBox::critical(this, "Error", "You must fill in your login / password");
  else {
    LoginInfos	*infos = new LoginInfos;
    infos->pseudo = ui.le_Login->text().toStdString();
    infos->pass = ui.le_Pass->text().toStdString();
    Client::getInstance()->connection(infos);
    _wMan->hideLogin();
    _wMan->showCharacter();
  }
}

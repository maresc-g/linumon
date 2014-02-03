//
// LoginView.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Oct 18 11:04:31 2013 cyril jourdain
// Last update Mon Feb  3 16:24:07 2014 guillaume marescaux
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
    std::string		pseudo = ui.le_Login->text().toStdString();
    std::string		pass = ui.le_Pass->text().toStdString();
    Client::getInstance()->connection(pseudo, pass);
    while (**(_wMan->getState()) == LOGIN);
    if (**(_wMan->getState()) == CHOOSE_PLAYER) {
      _wMan->hideLogin();
      _wMan->showCharacter();
    }
    else {
      QMessageBox::critical(this, "Error", "Unable to connect");
      *(_wMan->getState()) = LOGIN;
    }
  }
}

//
// ErrorBox.cpp for  in /home/jourda_c/GIT/linumon/MMO/Client
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Mar 18 20:48:43 2014 cyril jourdain
// Last update Tue Mar 18 21:06:56 2014 cyril jourdain
//

#include			"Common/ErrorBox.hh"

ErrorBox::ErrorBox(QWidget *)
{
}

ErrorBox::~ErrorBox()
{
}

void				ErrorBox::operator()(std::string const &title,
						     std::string const &message,
						     QWidget *w)
{
  printError(title, message, w);
}

void				ErrorBox::printError(std::string const &title,
						     std::string const &message,
						     QWidget *w)
{
  QMessageBox::critical(w, QString(title.c_str()), QString(message.c_str()));
}

//
// ErrorBox.cpp for  in /home/jourda_c/GIT/linumon/MMO/Client
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Mar 18 20:48:43 2014 cyril jourdain
// Last update Sat Mar 22 17:52:15 2014 guillaume marescaux
//

#include			"Common/ErrorBox.hh"

ErrorBox::ErrorBox(QWidget *):
  _title(""), _msg("")
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

void				ErrorBox::setInfos(std::string const &title, std::string const &msg)
{
  _title = title;
  _msg = msg;
}

void				ErrorBox::update()
{
  if (_msg != "")
    {
      printError(_title, _msg);
      _msg = "";
      _title = "";
    }
}

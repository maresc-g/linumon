//
// ErrorBox.hh for  in /home/jourda_c/GIT/linumon/MMO/Client
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Mar 18 20:42:41 2014 cyril jourdain
// Last update Tue Mar 18 21:06:27 2014 cyril jourdain
//

#ifndef 		__ERRORBOX_HH__
# define 		__ERRORBOX_HH__

#include		<QWidget>
#include		<QMessageBox>

class			ErrorBox
{
public:
  ErrorBox(QWidget *);
  virtual ~ErrorBox();

public:
  void			operator()(std::string const &title, std::string const &message,
				   QWidget *w = NULL);
  void			printError(std::string const &title, std::string const &message,
				   QWidget *w = NULL);
};

#endif

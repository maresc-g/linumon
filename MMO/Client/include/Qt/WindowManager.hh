//
// WindowManager.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 13:15:41 2013 cyril jourdain
// Last update Mon Feb  3 12:49:00 2014 cyril jourdain
//

#ifndef 		__WINDOWMANAGER_HH__
# define 		__WINDOWMANAGER_HH__

#include        <Qt/qapplication.h>
#include        <Qt/qframe.h>
#include	<Qt/qpushbutton.h>
#include	<Qt/qfile.h>
#include	<Qt/qgridlayout.h>
#include	"Qt/LoginView/LoginView.hh"
#include	"Qt/CharacterView/CharacterView.hh"
#include	"SFML/SFMLView.hpp"
#include	"Client.hh"


class	LoginView;
class	CharacterView;
class	SFMLView;

class			WindowManager
{
private:
  QApplication		*_app;
  QGridLayout		*_mainLayout;
  QFrame		*_mainFrame;
  MutexVar<eState>	*_state;
  LoginView		*_loginView;
  CharacterView		*_characterView;
  SFMLView		*_sfmlView;

public:
  WindowManager(int, char **, MutexVar<eState> *);
  virtual ~WindowManager();

public:
  int			exec();
  void			showLogin();
  void			hideLogin();
  void			showCharacter();
  void			hideCharacter();
  void			showSfmlView();
  void			hideSfmlView();
  MutexVar<eState>	*getState();
};

#endif

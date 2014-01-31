//
// WindowManager.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 13:49:38 2013 cyril jourdain
// Last update Thu Jan 30 13:52:38 2014 cyril jourdain
//

#include		"Qt/WindowManager.hh"
#include	<iostream>

WindowManager::WindowManager(int ac, char **av) :
  _app(new QApplication(ac, av)),
  _mainLayout(new QGridLayout),
  _mainFrame(new QFrame)
{
  _mainFrame->setWindowTitle("Qt SFML");
  _mainFrame->resize(1600, 1200);
  _mainFrame->show();
  _loginView = new LoginView(_mainFrame, this);
  _characterView = new CharacterView(_mainFrame, this);
  _sfmlView = new SFMLView(_mainFrame, QPoint(0,0), QSize(1600,1200), this);

  _mainLayout->addWidget(_loginView);
  _mainLayout->addWidget(_characterView);
  //_mainLayout->addWidget(_sfmlView);
  showCharacter();
  _mainFrame->setLayout(_mainLayout);
  _mainLayout->setMargin(0);
  //hideCharacter();
  hideSfmlView();
  showLogin();
  //hideLogin();
  hideCharacter();
}

WindowManager::~WindowManager()
{  
}

int			WindowManager::exec()
{
  QFile File("../Res/stylesheet.qss");
  File.open(QFile::ReadOnly);

  QString styleSheet = QLatin1String(File.readAll());
  _app->setAttribute(Qt::AA_NativeWindows);
  _app->setStyleSheet(styleSheet);
  
  return (_app->exec());
}

void			WindowManager::showLogin() 
{
  // _mainLayout->addWidget(_loginView);
  _loginView->show();
}

void			WindowManager::hideLogin()
{
  // _mainLayout->removeWidget(_loginView);
  _loginView->hide();
}

void			WindowManager::showCharacter()
{
  // _mainLayout->addWidget(_characterView);
  _characterView->show();
}

void			WindowManager::hideCharacter()
{
  // _mainLayout->removeWidget(_characterView);
  _characterView->hide();
}

void			WindowManager::showSfmlView()
{
  _sfmlView->show();
}

void			WindowManager::hideSfmlView()
{
  _sfmlView->hide();
}
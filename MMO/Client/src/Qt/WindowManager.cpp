//
// WindowManager.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 13:49:38 2013 cyril jourdain
// Last update Tue Mar 11 14:33:28 2014 laurent ansel
//

#include	"Qt/WindowManager.hh"
#include	"Sound/SoundManager.hh"
#include	<iostream>

WindowManager::WindowManager(int &ac, char **av, MutexVar<CLIENT::eState> *state,
			     MutexVar<std::list<PlayerView *> *> *players,
			     MutexVar<Player*> *player,
			     MutexVar<bool> *newPlayer,
			     MutexVar<Battle*> *battle) :
  _app(new QApplication(ac, av)),
  _mainLayout(new QGridLayout),
  _mainFrame(new QFrame),
  _state(state),
  _mainPlayer(player),
  _players(players),
  _newPlayer(newPlayer),
  _battle(battle)
{
  _mainFrame->setWindowTitle("Qt SFML");
  _mainFrame->resize(WIN_W, WIN_H);
  _mainFrame->show();
  _loginView = new LoginView(_mainFrame, this);
  _characterView = new CharacterView(_mainFrame, this);
  _sfmlView = new SFMLView(_mainFrame, QPoint(0,0), QSize(WIN_W,WIN_H), this);

  _mainLayout->addWidget(_loginView);
  _mainLayout->addWidget(_characterView);
  //_mainLayout->addWidget(_sfmlView);
  _mainFrame->setLayout(_mainLayout);
  _mainLayout->setMargin(0);
  hideSfmlView();
  hideCharacter();
  showLogin();
  SoundManager::getInstance()->loadDefaultSounds();
  SoundManager::getInstance()->playMusic(MENU_THEME);
}

WindowManager::~WindowManager()
{  
  delete _mainLayout;
  delete _mainFrame;
  // delete _loginView;
  // delete _characterView;
  // delete _sfmlView;
}

int			WindowManager::exec()
{
  QFile File("./Res/stylesheet.qss");
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
  _characterView->clear();
  if (**_players && (**_players)->size() > 0)
    _characterView->setPlayers(***_players);
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

MutexVar<CLIENT::eState>	*WindowManager::getState()
{
  return _state;
}

MutexVar<Player*>		*WindowManager::getMainPlayer()
{
  return _mainPlayer;
}

MutexVar<bool>			*WindowManager::getNewPlayer()
{
  return _newPlayer;
}

MutexVar<Battle*>		*WindowManager::getBattle()
{
  return _battle;
}

SFMLView		*WindowManager::getSFMLView(void)
{
  return (_sfmlView);
}

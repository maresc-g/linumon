//
// Healer.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 20 13:16:32 2014 cyril jourdain
// Last update Fri Mar 21 00:39:16 2014 cyril jourdain
//

#include			"SFML/Window/ComputerScreen.hh"
#include			"SFML/Entities/Healer.hh"
#include			"SFML/WorldView.hh"
#include			<QMenu>

namespace ClientEntities {

  Healer::Healer(SFMLView *sfml) :
    Sprite(), _sfmlView(sfml)
  {
  }

  Healer::~Healer()
  {
  }

  void				Healer::onClick(QMouseEvent *event)
  {
    QMenu menu;
    
    menu.addAction("Use");
    QAction *action = menu.exec(QPoint(event->globalX(), event->globalY()));
    if (action)
      {
	if (action->text() == "Use")
	  {
	    std::cout << "I'm gonna heal you bro" << std::endl;
	    static_cast<WorldView *>(_sfmlView->getCurrentView())->setCurrentWindow(new ComputerScreen(_sfmlView,"Hi. Do you want to heal your mobs ?"));
	  }
      }
  }
}

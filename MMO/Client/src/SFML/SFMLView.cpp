//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Thu Feb 20 10:50:36 2014 guillaume marescaux
//

/*

  Need to :	Add bubble when getting message (using player pos ?)
		Add border on map
		Other entities
		
		Test loading another map

		TO DO FIRST :
		get the player real position at start.
		check if it can move (map border)
 */


#include		"SFML/SFMLView.hpp"
#include		"Map/Map.hh"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()), _mainPerso(NULL),
  _clock(new sf::Clock()), _sprites(new SpriteMap), _keyDelayer(new KeyDelayer()),
  _spellBar(new SpellBarView(this, w)), _itemView(new ItemView(this, w)),
  _inventory(new InventoryView(this, w)), _stuff(new StuffView(this, w)),
  _chat(new ChatView(this, w)), _menu(new MenuView(this, w))
{
  _textureTest = new sf::Texture();
  _textureTest->loadFromFile("./Res/test.png");
  _spriteTest = new sf::Sprite(*_textureTest);
  _spriteTest->setScale(4,4);
  _spellBar->hide();
  _itemView->hide();
  _stuff->hide();
  _inventory->hide();
  _menu->move(WIN_W / 2 - _menu->size().width() / 2, WIN_H / 2 - _menu->size().height() / 2);
  _menu->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _winTexture = new sf::RenderTexture();
  _winTexture->create(100*CASE_SIZE, 100*CASE_SIZE);
  _winSprite = new sf::Sprite();
  _changed = false;
  // _mainPName = new sf::Text();
  _textFont = new sf::Font();
  if (!_textFont->loadFromFile("./Res/arial.ttf"))
     std::cout << "Error while loading font" << std::endl;
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  /* Stuff needed when loading the view */
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadAnimations("./Res/perso1.json");
  _sMan->loadAnimations("./Res/textures.json");
  /* MUST be the first things to do */
  _clock->restart();
  loadPlayerList();
  loadMap();
  _mainPerso = new PlayerSprite();
  _sMan->copySprite("perso1", *_mainPerso);
  _mainPerso->setFont(_textFont);
  _mainPerso->setText(sf::String((**(_wMan->getMainPlayer()))->getName()));
  _mainPerso->play("default_down");
  _mainPerso->generateOffset();
  _mainPerso->setPosition((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE,
  			  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - _mainPerso->getCurrentBound()->height / 2 + 4);
  _mainView->move((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE - WIN_W / 2,
  		  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - WIN_H / 2);
  _inventory->initInventory();
  _stuff->initStuff();
  /* Theorically, generateOffset should be called everytime play() is called with another anim.
   But as far as i know, they are all of the same size, so offsets are OK for eveyone */
}

void			SFMLView::onUpdate()
{
  sf::Event event;

  while (pollEvent(event))
    ; /* Not used here but SFML need it to handle internal events */

  clear(sf::Color(0,0,0));
  drawView();
  checkKeys();
  _clock->restart();
  _chat->update();
}

void			SFMLView::onResize(QResizeEvent *e)
{
  setSize(sf::Vector2u(e->size().width(), e->size().height()));
}

void			SFMLView::drawView()
{
  if (!_changed){
    reloadBackgroundSprite();
  }
  _winSprite->setTexture(_winTexture->getTexture());
  draw(*_winSprite);
  if (_mainPerso) {
    _mainPerso->update(*_clock);
    draw(*_spriteTest);
    draw(*_mainPerso);
  }
}

void			SFMLView::checkKeys()
{
  _keyDelayer->update(_clock);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_mainPerso->isMoving())
    {
      if (Client::getInstance()->move(CLIENT::DOWN))
	_mainPerso->moveDown();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_mainPerso->isMoving())
    {
      if (Client::getInstance()->move(CLIENT::UP))
	_mainPerso->moveUp();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_mainPerso->isMoving())
    {
      if (Client::getInstance()->move(CLIENT::LEFT))
	_mainPerso->moveLeft();
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_mainPerso->isMoving())
    {
      if (Client::getInstance()->move(CLIENT::RIGHT))
	_mainPerso->moveRight();
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    _mainPerso->setSpeed(PX_PER_SECOND + 100);
  else
    _mainPerso->setSpeed(PX_PER_SECOND);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && _keyDelayer->isAvailable(sf::Keyboard::I) && !_chat->getFocused())
    {
      if (!_inventory->isVisible())
	_inventory->show();
      else
	_inventory->hide();
      _keyDelayer->addWatcher(sf::Keyboard::I, 100000);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && _keyDelayer->isAvailable(sf::Keyboard::Escape) && !_chat->getFocused())
    {
      if (!_menu->isVisible())
	_menu->show();
      else
	_menu->hide();
      _keyDelayer->addWatcher(sf::Keyboard::Escape, 100000);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) &&
      _keyDelayer->isAvailable(sf::Keyboard::Return))
    {
      if (!_chat->getFocused())
	_chat->setFocused(true);
      else
	_chat->submitText();
      _keyDelayer->addWatcher(sf::Keyboard::Return, 100000);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && _keyDelayer->isAvailable(sf::Keyboard::S) && !_chat->getFocused())
    {
      if (!_stuff->isVisible())
	_stuff->show();
      else
	_stuff->hide();
      _keyDelayer->addWatcher(sf::Keyboard::S, 100000);
    }
  if (_mainPerso->isMoving())
    _mainPerso->updateMoves(_clock, _mainView);
  setView(*_mainView);
}

void			SFMLView::loadPlayerList()
{
  // std::cout << " \nplayerList\n" << std::endl;

  // std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  
  std::cout << "Zone name : " <<  Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName() << std::endl;
  std::cout << "Player number : " << list.size() << std::endl;

  for (auto it = list.begin(); it != list.end(); it++)
    {
      std::cout << (static_cast<Player*>(*it))->getX() << std::endl;
    }
}

void			SFMLView::loadMap()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());

  for (int y = 0; y != zone->getSizeX(); y++)
    {
      for (int x = 0; x != zone->getSizeY(); x++)
	{
	  ((*_sprites)[y])[x] = _sMan->copySprite("grass");
	  ((*_sprites)[y])[x]->play("default");
	}
    }
  // for (auto it = cases->begin(); it != cases->end(); ++it)
  //   {
  //     std::cout << (*it)->getSafe() << std::endl;
  //   }
}

void			SFMLView::reloadBackgroundSprite()
{
  _winTexture->clear(sf::Color(0,0,0));
  for (unsigned int y = 0; y != _sprites->size(); ++y)
    {
      for (unsigned int x = 0; x != (*_sprites)[y].size(); ++x)
	{
	  (*_sprites)[y][x]->setPosition(x * CASE_SIZE, y * CASE_SIZE);
	  (*_sprites)[y][x]->update(*_clock);
	  _winTexture->draw(*((*_sprites)[y][x]));
	}
    }
  _winTexture->display();
  _changed = true;
}

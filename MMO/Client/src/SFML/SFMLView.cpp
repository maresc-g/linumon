//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Tue Feb 18 15:47:54 2014 cyril jourdain
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
  _chat->move(0, WIN_H - _chat->size().height());
  _winTexture = new sf::RenderTexture();
  _winTexture->create(100*50, 100*50);
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
  _mainPerso->setPosition(WIN_W / 2, WIN_H / 2);
  _mainPerso->play("default_down");
  _mainPerso->generateOffset();
  _inventory->initInventory();
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
      _mainPerso->moveDown();
      Client::getInstance()->move(CLIENT::DOWN);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_mainPerso->isMoving())
    {
      _mainPerso->moveUp();
      Client::getInstance()->move(CLIENT::UP);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_mainPerso->isMoving())
    {
      _mainPerso->moveLeft();
      Client::getInstance()->move(CLIENT::LEFT);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_mainPerso->isMoving())
    {
      _mainPerso->moveRight();
      Client::getInstance()->move(CLIENT::RIGHT);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && _keyDelayer->isAvailable(sf::Keyboard::I) && !_chat->getFocused())
    {
      if (!_inventory->isVisible())
	_inventory->show();
      else
	_inventory->hide();
      _keyDelayer->addWatcher(sf::Keyboard::I, 100000);
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
  for (unsigned int y = 0; y != _sprites->size() - 1; ++y)
    {
      for (unsigned int x = 0; x != (*_sprites)[y].size() - 1; ++x)
	{
	  (*_sprites)[y][x]->setPosition(x * 50, y * 50);
	  (*_sprites)[y][x]->update(*_clock);
	  _winTexture->draw(*((*_sprites)[y][x]));
	}
    }
  _winTexture->display();
  _changed = true;
}

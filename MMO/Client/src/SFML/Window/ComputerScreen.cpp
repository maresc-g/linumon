//
// ComputerScreen.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 20 16:17:20 2014 cyril jourdain
// Last update Fri Mar 21 13:00:40 2014 cyril jourdain
//

#include			"SFML/WorldView.hh"
#include			"SFML/Window/ComputerScreen.hh"
#include			<iostream>

ComputerScreen::ComputerScreen(SFMLView *s) :
  Window(s), _background(new Sprite()), _arrow(new Sprite()), _text(TEXT), _textDraw(new sf::Text()),
  _yes(new sf::Text()), _no(new sf::Text()), _pos(0), _selection(_yes)
{
  _sfmlView->getSpriteManager()->copySprite("ComputerScreen", *_background);
  _sfmlView->getSpriteManager()->copySprite("Arrow", *_arrow);
  _background->play("default");
  (*_background)["default"]->setLoopPlay(true);
  _arrow->play("default");
  (*_arrow)["default"]->setLoopPlay(true);
  _background->scale(2,2);
  _background->setPosition(WIN_W / 2 - (_background->getCurrentBound()->width * _background->getScale().x) / 2, WIN_H / 2 - (_background->getCurrentBound()->height * _background->getScale().y) / 2);
  initText(_textDraw, "");
  initText(_yes, "Yes");
  initText(_no, "No");
  _textDraw->setPosition(_background->getPosition().x + 90, _background->getPosition().y + 90);
  _yes->setPosition(_background->getPosition().x + 200, _background->getPosition().y + 350);
  _no->setPosition(_background->getPosition().x + 300, _background->getPosition().y + 350);
  _arrow->setPosition(_selection->getPosition().x - 45, _selection->getPosition().y + 5);
  _clock.restart();
  setModal(true);
}

ComputerScreen::ComputerScreen(SFMLView *s, std::string const &text) :
  Window(s), _background(new Sprite()), _arrow(new Sprite()), _text(text), _textDraw(new sf::Text()),
  _yes(new sf::Text()), _no(new sf::Text()), _pos(0), _selection(_yes)
{
  _sfmlView->getSpriteManager()->copySprite("ComputerScreen", *_background);
  _sfmlView->getSpriteManager()->copySprite("Arrow", *_arrow);
  _background->play("default");
  (*_background)["default"]->setLoopPlay(true);
  _arrow->play("default");
  (*_arrow)["default"]->setLoopPlay(true);
  _background->scale(2,2);
  _background->setPosition(WIN_W / 2 - (_background->getCurrentBound()->width * _background->getScale().x) / 2, WIN_H / 2 - (_background->getCurrentBound()->height * _background->getScale().y) / 2);
  initText(_textDraw, "");
  initText(_yes, "Yes");
  initText(_no, "No");
  _textDraw->setPosition(_background->getPosition().x + 90, _background->getPosition().y + 90);
  _yes->setPosition(_background->getPosition().x + 200, _background->getPosition().y + 350);
  _no->setPosition(_background->getPosition().x + 300, _background->getPosition().y + 350);
  _arrow->setPosition(_selection->getPosition().x - 45, _selection->getPosition().y + 5);
  _clock.restart();
  setModal(true);
}


ComputerScreen::~ComputerScreen()
{
}

void				ComputerScreen::draw() const
{
  _sfmlView->setView(_sfmlView->getDefaultView());
  _sfmlView->draw(*_background);
  _sfmlView->draw(*_textDraw);
  if (_pos >= _text.size()){
    _sfmlView->draw(*_yes);
    _sfmlView->draw(*_no);
    _sfmlView->draw(*_arrow);
  }
  _sfmlView->setView(*_sfmlView->getMainView());
}

void				ComputerScreen::update(sf::Clock &clock)
{
  _arrow->setPosition(_selection->getPosition().x - 45, _selection->getPosition().y + 5);
  if (_clock.getElapsedTime().asMicroseconds() > 35000)
    {
      _pos += _clock.getElapsedTime().asMicroseconds() / 50000;
      if (_text[_pos] == '$')
	_pos += 2;
      _clock.restart();
    }
  _textDraw->setString(_text.substr(0,_pos));
  _background->update(clock);
  _arrow->update(clock);
}

void				ComputerScreen::onKeyEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Left)
    _selection = _yes;
  if (event->key() == Qt::Key_Right)
    _selection = _no;
  if (event->key() == Qt::Key_Return)
    {
      if (_selection == _yes)
	Client::getInstance()->heal();
      else
	static_cast<WorldView*>(_sfmlView->getCurrentView())->setCurrentWindow(NULL);
    }
}

void				ComputerScreen::onMouseEvent(QMouseEvent *)
{
}

void				ComputerScreen::initText(sf::Text *t, std::string const &str)
{
  t->setFont(*_sfmlView->getFont());
  t->setString(str);
  t->setCharacterSize(22);
  t->setColor(sf::Color(15,230,30));
  t->setStyle(sf::Text::Bold);
}

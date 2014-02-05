//
// CharDescription.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 15:47:27 2013 cyril jourdain
// Last update Tue Feb  4 16:25:27 2014 guillaume marescaux
//

#include		"Qt/CharDescription/CharDescription.hh"

CharDescription::CharDescription(QWidget *parent, PlayerView const &player) :
  QWidget(parent), _player(new PlayerView(player))
{
  ui.setupUi(this);
  ui.l_name->setText(player.name.c_str());
  ui.l_level->setText(std::string("Level " + std::to_string(player.level)).c_str());
}

CharDescription::~CharDescription()
{
  delete _player;
}

void		CharDescription::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

PlayerView const	&CharDescription::getPlayer(void) const
{
  return (*_player);
}

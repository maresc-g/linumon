//
// GuildView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar 13 16:28:22 2014 guillaume marescaux
// Last update Thu Mar 13 16:47:17 2014 guillaume marescaux
//

#ifndef 		__GUILDVIEW_HH__
# define 		__GUILDVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_guildview.h"
#include		"Qt/WindowManager.hh"

class			GuildView : public QWidget
{
  Q_OBJECT

public:

  GuildView(QWidget *, WindowManager *wMan);
  virtual ~GuildView();

private:

  Ui::guildview		ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

public:

  void			initGuild(Guild const *guild);
};

#endif

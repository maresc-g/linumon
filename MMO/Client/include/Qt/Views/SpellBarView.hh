//
// SpellBarView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 15:32:26 2014 guillaume marescaux
// Last update Wed Mar  5 15:29:16 2014 guillaume marescaux
//

#ifndef 		__SPELLBARVIEW_HH__
# define 		__SPELLBARVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		<QSignalMapper>
#include		"ui_spellbarview.h"
#include		"Qt/WindowManager.hh"
#include		"Entities/Spells.hh"

class			WindowManager;

class			SpellBarView : public QWidget
{
  Q_OBJECT

public:

  SpellBarView(QWidget *, WindowManager *wMan = NULL);
  virtual ~SpellBarView();

private:

  Ui::spellbarview	ui;
  WindowManager		*_wMan;
  std::list<QPushButton *>	*_buttons;
  Spells const		*_spells;
  QSignalMapper		*_mapper;

private:

  virtual void		paintEvent(QPaintEvent *);

public slots:

  void			handleClick(QString const &name);

public:

  void			setInfos(Spells const &spells);
};

#endif

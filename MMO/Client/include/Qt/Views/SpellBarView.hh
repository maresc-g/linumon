//
// SpellBarView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 15:32:26 2014 guillaume marescaux
// Last update Fri Feb  7 10:53:57 2014 guillaume marescaux
//

#ifndef 		__SPELLBARVIEW_HH__
# define 		__SPELLBARVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_spellbar.h"
#include		"Qt/WindowManager.hh"

class			WindowManager;

class			SpellBarView : public QWidget
{
  Q_OBJECT

public:

  SpellBarView(QWidget *, WindowManager *wMan = NULL);
  ~SpellBarView();

private:

  Ui::SpellBarView	ui;
  WindowManager		*_wMan;

private:

  virtual void		paintEvent(QPaintEvent *);

public slots:

  void			on_b_spell1_clicked();
  void			on_b_spell2_clicked();
  void			on_b_spell3_clicked();
  void			on_b_spell4_clicked();
  void			on_b_spell5_clicked();
  void			on_b_spell6_clicked();
  void			on_b_spell7_clicked();
  void			on_b_spell8_clicked();
  void			on_b_spell9_clicked();
  void			on_b_spell10_clicked();
};

#endif

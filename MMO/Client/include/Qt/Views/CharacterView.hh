//
// CharacterView.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 13:02:41 2013 cyril jourdain
// Last update Mon Feb 10 14:22:06 2014 guillaume marescaux
//

#ifndef 		__CHARACTERVIEW_HH__
# define 		__CHARACTERVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_characterview.h"
#include		"Qt/WindowManager.hh"
#include		"Qt/CharDescription/CharDescription.hh"
#include		"Qt/Views/CreateCharView.hh"
#include		<QScrollArea>
#include		<QFrame>
#include		<vector>

class			WindowManager;
class			CreateCharView;

class			CharacterView : public QWidget
{
  Q_OBJECT

private: /* QT WIDGETS */
  WindowManager		*_wMan;
  QGridLayout		*_layout;
  std::vector<CharDescription *> *_charList;
  QPushButton		*_prev;
  QPushButton		*_next;
  QScrollArea		*_scrollArea;
  QFrame		*_charContainer;
  QHBoxLayout		*_charLayout;
  CreateCharView	*_createCharView;

private: /* ATTRIBUTES */
  unsigned int		_charNumber;

public:
  CharacterView(QWidget *, WindowManager *wMan = NULL);
  virtual ~CharacterView();

  void			clear();
  void			setPlayers(std::list<PlayerView *> const &players);

private:
  Ui::CharacterView	ui;

private:
  virtual void		paintEvent(QPaintEvent *);

private slots:
  void			b_prev_clicked();
  void			b_next_clicked();
  void			on_b_back_clicked();
  void			on_b_new_clicked();
  void			on_b_play_clicked();

};

#endif

//
// PlayerView.hh for PlayerView in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 10:15:18 2014 alexis mestag
// Last update Mon Feb  3 11:02:55 2014 alexis mestag
//

#ifndef				__PLAYERVIEW_HH__
# define			__PLAYERVIEW_HH__

# include			<string>
# include			"Entities/Player.hh"

class				PlayerView
{
public:
  std::string			name;
  int				level;
};

# ifdef	ODB_COMPILER
#  pragma db view(PlayerView) object(Player)
#  pragma db member(PlayerView::level) column(Player::_level._lvl)
# endif

#endif

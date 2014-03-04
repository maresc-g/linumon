//
// Players.hh for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:53:16 2013 alexis mestag
// Last update Mon Mar  3 16:35:14 2014 alexis mestag
//

#ifndef			__PLAYERS_HH__
# define		__PLAYERS_HH__

# include		<list>
# include		"Utility/Wrapper.hpp"

class			Player;

class			Players : public ContainerWrapper<std::list<Player *>>
{
private:
  Players(Players const &rhs);

  Players		&operator=(Players const &rhs);

public:
  Players();
  virtual ~Players();

  void			addPlayer(Player &player);
  void			deletePlayers();
};

# include		"Entities/Player.hh"

#endif

//
// Battle.hh for battle in /home/maitre_c/work/linumon/MMO/Common/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Tue Jan 28 15:37:45 2014 antoine maitre
// Last update Thu Jan 30 16:56:52 2014 antoine maitre
//

#ifndef				__BATTLE_HH__
# define			__BATTLE_HH__

# include			<string>
# include			"Entities/Player.hh"

class				Battle
{
public:
  enum				eBattle
    {
      PVE,
      PVP
    };
private:
  unsigned int const		_id;
  eBattle const			_type;
  int const			_mobNumber;
  std::list<Mob *>		_mobs1;
  std::list<Mob *>		_mobs2;
  Player			*_player1;
  Player			*_player2;
public:
  Battle(unsigned int const id, eBattle const type, int const mobNumber, Player *player1, Player *player2);
  ~Battle();
  unsigned int			getID() const;
  eBattle 			getType() const;
};

#endif

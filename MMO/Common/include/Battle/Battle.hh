//
// Battle.hh for battle in /home/maitre_c/work/linumon/MMO/Common/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Tue Jan 28 15:37:45 2014 antoine maitre
// Last update Tue Jan 28 15:57:43 2014 antoine maitre
//

#ifndef				__BATTLE_HH__
# define			__BATTLE_HH__

# include			<string>

class				Battle
{
public:
  enum				eBattle
    {
      PVE,
      PVP
    };
private:
  eBattle			_type;
  int				_mobNumber;
  std::list<Mob *>		*_mobs1;
  std::list<Mob *>		*_mobs2;
  APlayer			*_player1;
  APlayer			*_player2;
public:
  Battle();
  ~Battle();
};

#endif

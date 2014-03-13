//
// AI.hh for AI in /home/maitre_c/work/linumon/MMO/Server
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Sun Mar  2 22:31:17 2014 antoine maitre
// Last update Thu Mar 13 14:58:20 2014 antoine maitre
//

#ifndef			__AI_HH__
# define		__AI_HH__

# include		<tuple>
# include		"Entities/Player.hh"

class			AI : public Player
{
  Player		*_adv;
  std::list<Mob *>	_mobs;
public:
  AI(std::string const &name, std::string const &factionName = "");
  virtual ~AI();
  std::tuple<unsigned int const, unsigned int const, Spell const *>		action(unsigned int const);
  void		setAdv(Player *);
  void		addMob(Mob *mob);
  void		addEnemy(std::list<Mob *> mob);
  void		remove(unsigned int const target);
  int		getRandomMob(int);
  void		dswitch(unsigned int const target, unsigned int const targetBis);
};

#endif

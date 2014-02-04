//
// PlayerView.hh for PlayerView in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 10:15:18 2014 alexis mestag
// Last update Tue Feb  4 13:47:35 2014 laurent ansel
//

#ifndef				__PLAYERVIEW_HH__
# define			__PLAYERVIEW_HH__

# include			<string>
# include			"Entities/Player.hh"

class				PlayerView
{
public:
  unsigned long			persistentId;
  std::string			name;
  int				level;
  unsigned long			userId;
  std::string			faction;

public:
  PlayerView(unsigned long const id = 0, std::string const &playerName = "", int const playerLevel = 0, unsigned long const user = 0, std::string const &playerFaction = "")
    : persistentId(id), name(playerName), level(playerLevel), userId(user), faction(playerFaction) {}
  PlayerView(PlayerView const &rhs) {
    *this = rhs;
  }
  virtual ~PlayerView() {}

  PlayerView			&operator=(PlayerView const &rhs) {
    if (this != &rhs) {
      this->persistentId = rhs.persistentId;
      this->name = rhs.name;
      this->level = rhs.level;
      this->userId = rhs.userId;
      this->faction = rhs.faction;
    }
    return (*this);
  }
};

# ifdef	ODB_COMPILER
#  pragma db view(PlayerView) object(Player) object(User: Player::_user) object(Faction)
#  pragma db member(PlayerView::persistentId) column(Player::_persistentId)
#  pragma db member(PlayerView::name) column(Player::_name)
#  pragma db member(PlayerView::level) column(Player::_level._lvl)
#  pragma db member(PlayerView::userId) column(User::_persistentId)
#  pragma db member(PlayerView::faction) column(Faction::_name)
# endif

#endif

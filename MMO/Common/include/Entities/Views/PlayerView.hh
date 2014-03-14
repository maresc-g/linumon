//
// PlayerView.hh for PlayerView in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 10:15:18 2014 alexis mestag
// Last update Fri Mar 14 13:42:36 2014 laurent ansel
//

#ifndef				__PLAYERVIEW_HH__
# define			__PLAYERVIEW_HH__

# include			<string>
# include			"Entities/Player.hh"
# include			"Entities/User.hh"
# include			"Entities/Faction.hh"
# include			"Utility/ISerialization.hh"

class				PlayerView : public ISerialization
{
public:
  unsigned long			persistentId;
  std::string			name;
  unsigned int			level;
  unsigned long			userId;
  std::string			faction;
  std::string			guild;

public:
  PlayerView(unsigned long const id = 0, std::string const &playerName = "", int const playerLevel = 0,
	     unsigned long const user = 0, std::string const &playerFaction = "", std::string const &playerGuild = "") :
    persistentId(id), name(playerName), level(playerLevel), userId(user), faction(playerFaction),
    guild(playerGuild)
  {}
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
      this->guild = rhs.guild;
    }
    return (*this);
  }

  virtual bool		serialization(Trame &trame) const
  {
    bool		ret = true;

    trame["LVL"] = level;
    trame["FAC"] = faction;
    return (ret);
  }

  static PlayerView	*deserialization(Trame const &trame)
  {
    PlayerView		*view = new PlayerView;

    view->level = trame["LVL"].asUInt();
    view->faction = trame["FAC"].asString();
    return (view);
  }
};

# ifdef	ODB_COMPILER
#  pragma db view(PlayerView) object(Player) object(User: Player::_user) object(Faction: Player::_faction) object(Guild: Player::_guild)
#  pragma db member(PlayerView::persistentId) column(Player::_persistentId)
#  pragma db member(PlayerView::name) column(Player::_name)
#  pragma db member(PlayerView::level) column(Player::level)
#  pragma db member(PlayerView::userId) column(User::_persistentId)
#  pragma db member(PlayerView::faction) column(Faction::_name)
#  pragma db member(PlayerView::guild) column(Guild::_name)
# endif

#endif

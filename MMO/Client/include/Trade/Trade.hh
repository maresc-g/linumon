//
// Trade.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 10 16:56:18 2014 guillaume marescaux
// Last update Tue Mar 11 19:26:07 2014 guillaume marescaux
//

#ifndef 			__TRADE_HH__
# define 			__TRADE_HH__

#include			<string>
#include			"Entities/Mob.hh"
#include			"Entities/AItem.hh"

class				Trade
{
public:

  enum				eAction
    {
      PUT,
      GET
    };

  enum				ePerson
    {
      PLAYER,
      OTHER
    };

private:

  Trade(Trade const &);
  Trade				&operator=(Trade const &);

private:

  unsigned int			_id;
  std::string			_name;
  std::list<AItem const *>	*_playerItems;
  std::list<AItem const *>	*_otherItems;
  std::list<Mob const *>	*_playerMobs;
  std::list<Mob const *>	*_otherMobs;
  unsigned int			_playerMoney;
  unsigned int			_otherMoney;
  bool				_changed;

public:

  Trade();
  virtual ~Trade();

public:

  void				putPlayerMoney(unsigned int);
  void				putOtherMoney(unsigned int);
  void				getPlayerMoney(unsigned int);
  void				getOtherMoney(unsigned int);
  void				putPlayerMob(Mob const *);
  void				putOtherMob(Mob const *);
  void				getPlayerMob(Mob const *);
  void				getOtherMob(Mob const *);
  void				putPlayerItem(AItem const *);
  void				putOtherItem(AItem const *);
  void				getPlayerItem(AItem const *);
  void				getOtherItem(AItem const *);
  void				setName(std::string const &);
  void				setChanged(bool);

  unsigned int			getPlayerMoney(void) const;
  unsigned int			getOtherMoney(void) const;
  std::list<AItem const*> const	&getPlayerItems(void) const;
  std::list<AItem const*> const	&getOtherItems(void) const;
  std::list<Mob const*> const	&getPlayerMobs(void) const;
  std::list<Mob const*> const	&getOtherMobs(void) const;
  std::string const		&getName(void) const;
  unsigned int			getId(void) const;
  bool				getChanged(void) const;

  void				reset(unsigned int id, std::string const &name);
};

#endif

//
// Trade.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Mar 10 16:56:18 2014 guillaume marescaux
// Last update Sun Mar 16 14:15:28 2014 guillaume marescaux
//

#ifndef 			__TRADE_HH__
# define 			__TRADE_HH__

#include			<string>
#include			"Entities/Mob.hh"
#include			"Entities/AItem.hh"
#include			"Mutex/MutexVar.hpp"

class				Trade
{
public:

  enum				eResponse
    {
      ACCEPT,
      REFUSE,
      NONE
    };

private:

  Trade(Trade const &);
  Trade				&operator=(Trade const &);

private:

  unsigned int			_id;
  std::string			_name;
  std::list<Stack<AItem> const *>	*_playerStacks;
  std::list<Stack<AItem> const *>	*_otherStacks;
  std::list<Mob const *>	*_playerMobs;
  std::list<Mob const *>	*_otherMobs;
  unsigned int			_playerMoney;
  unsigned int			_otherMoney;
  eResponse			_playerResponse;
  eResponse			_otherResponse;
  bool				_end;
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
  void				putPlayerStack(Stack<AItem> const *);
  void				putOtherStack(Stack<AItem> const *);
  void				getPlayerStack(Stack<AItem> const *);
  void				getOtherStack(Stack<AItem> const *);
  void				setPlayerResponse(eResponse);
  void				setOtherResponse(eResponse);
  void				setName(std::string const &);
  void				setEnd(bool);
  void				setChanged(bool);

  unsigned int			getPlayerMoney(void) const;
  unsigned int			getOtherMoney(void) const;
  std::list<Stack<AItem> const *> const	&getPlayerStacks(void) const;
  std::list<Stack<AItem> const *> const	&getOtherStacks(void) const;
  std::list<Mob const*> const	&getPlayerMobs(void) const;
  std::list<Mob const*> const	&getOtherMobs(void) const;
  std::string const		&getName(void) const;
  unsigned int			getId(void) const;
  eResponse			getPlayerResponse(void) const;
  eResponse			getOtherResponse(void) const;
  bool				getEnd(void) const;
  bool				getChanged(void) const;

  void				reset(unsigned int id, std::string const &name);
  void				handleEnd(MutexVar<Player *> *player);
};

#endif

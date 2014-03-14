//
// GuildManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar 13 15:56:55 2014 laurent ansel
// Last update Thu Mar 13 20:24:15 2014 laurent ansel
//

#ifndef 			__GUILDMANAGER_HH__
# define 			__GUILDMANAGER_HH__

#include			"Trame/Trame.hh"

class				GuildManager
{
private:
  bool				gCreate(Trame *trame);
  bool				invite(Trame *trame);
  bool				refuse(Trame *trame);
  bool				accept(Trame *trame);
  bool				gQuit(Trame *trame);

public:
  GuildManager();
  virtual ~GuildManager();
};

#endif

//
// Invite.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Sat Mar 22 19:43:11 2014 guillaume marescaux
// Last update Sat Mar 22 19:46:41 2014 guillaume marescaux
//

#ifndef 		__INVITE_HH__
# define 		__INVITE_HH__

struct			Invite
{
  bool			invited;
  std::string		name;

  Invite(bool i, std::string n): invited(i), name(n) {}
};

#endif

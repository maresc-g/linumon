//
// eState.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:30:54 2014 guillaume marescaux
// Last update Mon Feb 10 14:05:55 2014 guillaume marescaux
//

#ifndef 		__ESTATE_HH__
# define 		__ESTATE_HH__

namespace		CLIENT
{
  enum			eState
    {
      LOGIN,
      CHOOSE_PLAYER,
      CREATE,
      PLAYING,
      BATTLE,
      TRADE,
      NONE
    };
}

#endif

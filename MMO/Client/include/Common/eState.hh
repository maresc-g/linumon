//
// eState.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:30:54 2014 guillaume marescaux
// Last update Fri Mar 14 17:41:59 2014 guillaume marescaux
//

#ifndef 		__ESTATE_HH__
# define 		__ESTATE_HH__

namespace		CLIENT
{
  enum			eState
    {
      LOGIN,
      CHOOSE_PLAYER,
      LOADING,
      CREATE,
      PLAYING,
      ENTER_BATTLE,
      LOADING_BATTLE,
      LEAVING_BATTLE,
      BATTLE,
      LAUNCH_TRADE,
      TRADE,
      LOADED,
      NEWZONE,
      NONE
    };
}

#endif

//
// eState.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:30:54 2014 guillaume marescaux
// Last update Wed Mar 12 14:00:15 2014 cyril jourdain
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
      TRADE,
      LOADED,
      NEWZONE,
      NONE
    };
}

#endif

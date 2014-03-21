//
// Healer.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Mar 20 12:57:37 2014 cyril jourdain
// Last update Thu Mar 20 15:27:20 2014 cyril jourdain
//

#ifndef 		__HEALER_HH__
# define 		__HEALER_HH__

# include		"SFML/Sprite/Sprite.hh"
# include		"SFML/SFMLView.hpp"

namespace ClientEntities{

  class			Healer : public Sprite
  {
  public:
    SFMLView		*_sfmlView;

  public:
    Healer(SFMLView *);
    virtual ~Healer();

  public:
    virtual void	onClick(QMouseEvent *);
  };

}
#endif

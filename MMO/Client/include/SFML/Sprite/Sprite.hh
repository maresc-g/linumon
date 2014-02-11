//
// Sprites.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 13:38:44 2014 cyril jourdain
// Last update Tue Feb 11 13:56:18 2014 cyril jourdain
//

#ifndef 		__SPRITE_HH__
# define 		__SPRITE_HH__

#include		<SFML/System.hpp>
#include		<SFML/Graphics.hpp>
#include		<map>
#include		<iostream>
#include		"SFML/Sprite/Animation.hh"

class			Sprite : public sf::Drawable, public sf::Transformable
{

private /* attributs */:
  sf::Texture		*_texture;
  std::map<std::string, Animation *>	*_anim;
  sf::Vertex		*_vertex;
  std::string		_current;
  bool			_playing;
  

public /* class specific */ :
  Sprite();
  Sprite(Sprite const &);
  Animation		*operator[](std::string const &id);
  virtual ~Sprite();

public /* inherited functions */ :
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
  virtual void		update(sf::Clock &);

public /* methods */ :
  void			setTexture(sf::Texture *);
  void			loadFromFile(std::string const path);
  void			addAnim(std::string const &name);
  void			play(std::string const &name);
  void			play();
  void			stop();
  void			pause();
  void			print();
  std::string		getLastPlayed();
};

#endif

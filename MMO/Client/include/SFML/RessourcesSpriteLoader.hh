//
// Ressources.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar 15 23:10:42 2014 cyril jourdain
// Last update Sun Mar 16 19:02:06 2014 cyril jourdain
//

#ifndef 		__RESSOURCESSPRITELOADER_HH__
# define 		__RESSOURCESSPRITELOADER_HH__

#include		<map>
#include		"SFML/RessourceSprite.hh"
#include		"Qt/WindowManager.hh"

class			RessourcesSpriteLoader
{

private:
  typedef std::map<std::string, void (RessourcesSpriteLoader::*)(AEntity *)>	RessourceLoadMap;
  typedef std::list<Sprite *>					Layer;
  typedef std::vector<Layer *>					LayerList;
  WindowManager		*_wMan;
  RessourceLoadMap	*_loadMap;
  LayerList	*_layers;

public:
  RessourcesSpriteLoader(WindowManager *);
  virtual ~RessourcesSpriteLoader();

public:
  void			loadRessources();
  void			drawLayer(unsigned int layerId);
  void			onMouseEvent(QMouseEvent *event);

private:
  void			defaultLoader(AEntity *);
  void			treeLoader(AEntity *);
  void			healerLoader(AEntity *);
  void			houseLoader(AEntity *);
};

#endif

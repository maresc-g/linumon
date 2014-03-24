//
// Ressources.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar 15 23:10:42 2014 cyril jourdain
// Last update Mon Mar 24 17:41:22 2014 cyril jourdain
//

#ifndef 		__RESSOURCESSPRITELOADER_HH__
# define 		__RESSOURCESSPRITELOADER_HH__

#include		<map>
#include		"SFML/RessourceSprite.hh"
#include		"Qt/WindowManager.hh"

class			RessourcesSpriteLoader
{

public:
  enum eLayer{
    FLOOR_LAYER = 0,
    ON_FLOOR_LAYER,
    PNJ_LAYER,
    TOP_LAYER,
    CARCASS_LAYER
  };

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
  void			checkCarcass();

private:
  void			defaultLoader(AEntity *);
  void			treeLoader(AEntity *);
  void			healerLoader(AEntity *);
  void			houseLoader(AEntity *);
};

#endif

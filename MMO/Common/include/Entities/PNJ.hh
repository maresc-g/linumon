//
// PNJ.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 13:42:08 2014 laurent ansel
// Last update Tue Feb 25 14:35:01 2014 laurent ansel
//

#ifndef 		__PNJ_HH__
# define		__PNJ_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AEntity.hh"
# include		"Utility/ISerialization.hh"
# include		"Zone/Coordinate.hpp"
# include		"Utility/Id.hh"
# include		"Entities/Digitaliser.hh"
# include		"Entities/Player.hh"

class			PNJ : public AEntity, public ISerialization
{
public:
  typedef iCoordinate	PNJCoordinate;

  typedef enum		ePnj
    {
      NONE,
      HEAL
    }			ePnj;
private:
  ePnj			_pnjType;

private:
  PNJCoordinate		*_coord;

public:
  PNJ(std::string const &name = "PNJ");
  PNJ(PNJ const &rhs);
  virtual ~PNJ();

  PNJ			&operator=(PNJ const &rhs);

  PNJCoordinate const	&getCoord() const;
  void				setCoord(PNJCoordinate const &coord);
  PNJCoordinate::type const	&getX() const;
  PNJCoordinate::type const	&getY() const;
  void			setX(PNJCoordinate::type const &x);
  void			setY(PNJCoordinate::type const &y);

  virtual bool		action(Player *player) = 0;

  void			setPNJType(ePnj const pnjType);
  PNJ::ePnj		getPNJType() const;


  virtual bool		serialization(Trame &trame) const = 0;
  static PNJ		*deserialization(Trame const &trame, bool const client = true);
};

#endif

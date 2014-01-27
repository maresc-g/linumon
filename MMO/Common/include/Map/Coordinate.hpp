//
// Coordinate.hpp for Coordinate in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 16:59:07 2013 alexis mestag
// Last update Mon Jan 27 13:13:02 2014 laurent ansel
//

#ifndef			__COORDINATE_HPP__
# define		__COORDINATE_HPP__

# include		"Utility/ISerialization.hh"

template<typename T>
class			Coordinate : public ISerialization
{
public:
  typedef T		type;

private:
  T			_x;
  T			_y;

public:
  Coordinate(T const &x = T(), T const &y = T()) : _x(x), _y(y) {}
  Coordinate(Coordinate const &rhs) {
    *this = rhs;
  }
  virtual ~Coordinate() {}

  Coordinate		&operator=(Coordinate const &rhs) {
    if (this != &rhs) {
      this->setX(rhs.getX());
      this->setY(rhs.getY());
    }
    return (*this);
  }

  T const		&getX() const {
    return (_x);
  }
  void			setX(T const &x) {
    _x = x;
  }

  T const		&getY() const {
    return (_y);
  }
  void			setY(T const &y) {
    _y = y;
  }

  /*
  ** EXCEPTION !!!!!
  ** trame => trame[CONTENT]["PLAYER" or "CASE" or ...]
  */

  bool			serialization(Trame &trame) const
  {
    bool		ret = true;

    trame["COORDINATE"]["X"] = _x;
    trame["COORDINATE"]["Y"] = _y;
    return (ret);
  }

  bool			deserialization(Trame const &trame)
  {
    bool		ret = true;

    if (trame.isMember("COORDINATE"))
      {
	if (trame["COORDINATE"]["X"].isInt())
	  _x = trame["COORDINATE"]["X"].asInt();
	else if (trame["COORDINATE"]["X"].isDouble())
	  _x = trame["COORDINATE"]["X"].asDouble();
	if (trame["COORDINATE"]["Y"].isInt())
	  _y = trame["COORDINATE"]["Y"].asInt();
	else if (trame["COORDINATE"]["Y"].isDouble())
	  _y = trame["COORDINATE"]["Y"].asDouble();
      }
    return (ret);
  }

};

typedef Coordinate<int>	iCoordinate;

#endif

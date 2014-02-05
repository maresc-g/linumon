//
// Coordinate.hpp for Coordinate in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 16:59:07 2013 alexis mestag
// Last update Wed Feb  5 15:24:06 2014 laurent ansel
//

#ifndef			__COORDINATE_HPP__
# define		__COORDINATE_HPP__

# include		<typeinfo>
# include		"Utility/ISerialization.hh"
# include		"ObjectPool/ObjectPoolManager.hpp"

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

  bool			serialization(Trame &trame) const
  {
    bool		ret = true;

    trame["COORDINATE"]["X"] = _x;
    trame["COORDINATE"]["Y"] = _y;
    return (ret);
  }

  static Coordinate<T>	*deserialization(Trame const &trame)
  {
    Coordinate<T>	*coord = NULL;

    if (trame.isMember("COORDINATE"))
      {
	if (typeid(T) == typeid(int))
	  ObjectPoolManager::getInstance()->setObject(coord, "coordinateint");
	else if (typeid(T) == typeid(double))
	  ObjectPoolManager::getInstance()->setObject(coord, "coordinatedouble");
	if (coord && trame["COORDINATE"].isMember("X") && trame["COORDINATE"].isMember("X"))
	  {
	    coord->setX(trame["COORDINATE"]["X"].isDouble());
	    coord->setY(trame["COORDINATE"]["Y"].isDouble());
	  }
      }
    return (coord);
  }

};

typedef Coordinate<int>	iCoordinate;

#endif

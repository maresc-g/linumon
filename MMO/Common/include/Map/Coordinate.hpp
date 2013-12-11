//
// Coordinate.hpp for Coordinate in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 16:59:07 2013 alexis mestag
// Last update Thu Dec  5 18:30:32 2013 alexis mestag
//

#ifndef			__COORDINATE_HPP__
# define		__COORDINATE_HPP__

# include		<odb/core.hxx>

template<typename T>
class			Coordinate
{
  friend class		odb::access;

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
};

typedef Coordinate<int>	iCoordinate;

#endif

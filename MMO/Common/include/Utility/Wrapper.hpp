//
// Wrapper.hpp for Wrapper in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Feb 28 13:17:26 2014 alexis mestag
// Last update Fri Feb 28 14:12:07 2014 alexis mestag
//

#ifndef				__WRAPPER_HPP__
# define			__WRAPPER_HPP__

template<typename T>
class				Wrapper
{
public:
  typedef T			wrapped_type;

public:
  virtual ~Wrapper() {}
};

template<typename T>
class				ContainerWrapper : public Wrapper<T>
{
public:
  typedef typename Wrapper<T>::wrapped_type	container_type;

public:
  virtual ~ContainerWrapper() {}
};

#endif

//
// Repository.hpp for Repository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:22:57 2014 alexis mestag
// Last update Sat Feb  1 16:00:52 2014 alexis mestag
//

#ifndef				__REPOSITORY_HPP__
# define			__REPOSITORY_HPP__

# include			"Utility/Singleton.hpp"

template<typename T>
class				Repository : public Singleton<Repository<T> >
{
  friend class			Singleton<Repository<T> >;

private:
  Repository() :
    Singleton<Repository<T> >() {}
  virtual ~Repository() {}
};

#endif

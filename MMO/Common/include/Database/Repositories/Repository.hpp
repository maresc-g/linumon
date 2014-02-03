//
// Repository.hpp for Repository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:22:57 2014 alexis mestag
// Last update Mon Feb  3 17:38:27 2014 alexis mestag
//

#ifndef				__REPOSITORY_HPP__
# define			__REPOSITORY_HPP__

template<typename T>
class				Repository : public Singleton<Repository<T> >
{
  friend class			Singleton<Repository<T> >;

private:
  Repository() :
    Singleton<Repository<T> >() {}
  virtual ~Repository() {}
};

template<typename T>
class				BaseRepository : public Singleton<Repository<T> >
{
  friend class			Singleton<Repository<T> >;

protected:
  BaseRepository() : Singleton<Repository<T> >() {}
  virtual ~BaseRepository() {}

public:
  T				*getById(unsigned long id) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());
    T				*ret = Database::getInstance()->getDb()->find<T>(id);

    t.commit();
    return (ret);
  }
};

#endif

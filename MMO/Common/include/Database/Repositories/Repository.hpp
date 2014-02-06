//
// Repository.hpp for Repository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:22:57 2014 alexis mestag
// Last update Thu Feb  6 16:02:20 2014 alexis mestag
//

#ifndef				__REPOSITORY_HPP__
# define			__REPOSITORY_HPP__

# include			"Utility/Singleton.hpp"

template<typename T>
class				BaseRepository : public Singleton<Repository<T> >
{
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

  unsigned long			persist(T &o) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());

    Database::getInstance()->getDb()->persist(o);

    t.commit();
    return (o.getPersistentId());
  }

  void				update(T const &o) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());

    Database::getInstance()->getDb()->update(o);

    t.commit();
  }
};

template<typename T>
class				Repository : public BaseRepository<T>
{
  friend class			Singleton<Repository<T> >;

private:
  Repository() :
    BaseRepository<T>() {}
  virtual ~Repository() {}
};

#endif

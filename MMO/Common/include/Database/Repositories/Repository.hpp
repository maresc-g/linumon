//
// Repository.hpp for Repository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:22:57 2014 alexis mestag
// Last update Fri Mar  7 15:30:35 2014 alexis mestag
//

#ifndef				__REPOSITORY_HPP__
# define			__REPOSITORY_HPP__

# include			<list>
# include			"Utility/Singleton.hpp"
# include			"Database/Database.hpp"

template<typename T>
class				Repository;

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

  std::list<typename Database::ObjectTraits<T>::pointer_type>	getAll() {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());
    Database::Result<T>		result(Database::getInstance()->getDb()->query<T>());
    std::list<typename Database::ObjectTraits<T>::pointer_type>		ret;

    for (auto it = result.begin() ; it != result.end() ; ++it) {
      ret.push_back(it.load());
    }

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

  void				erase(T const &o) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());

    Database::getInstance()->getDb()->erase(o);

    t.commit();
  }

  void				removeFromCache(T const &o) {
    Session::_cache_erase<T>(*Database::getInstance()->getDb(), o.getPersistentId());
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

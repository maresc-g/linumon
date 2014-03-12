//
// Repository.hpp for Repository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:22:57 2014 alexis mestag
// Last update Tue Mar 11 11:16:49 2014 alexis mestag
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
  T				*getById(unsigned long id, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    T				*ret = Database::getInstance()->getDb()->find<T>(id);

    if (t) {
      t->commit();
      delete t;
    }
    return (ret);
  }

  std::list<typename Database::ObjectTraits<T>::pointer_type>	getAll(bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Result<T>		result(Database::getInstance()->getDb()->query<T>());
    std::list<typename Database::ObjectTraits<T>::pointer_type>		ret;

    for (auto it = result.begin() ; it != result.end() ; ++it) {
      ret.push_back(it.load());
    }

    if (t) {
      t->commit();
      delete t;
    }
    return (ret);
  }

  unsigned long			persist(T &o, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);

    Database::getInstance()->getDb()->persist(o);

    if (t) {
      t->commit();
      delete t;
    }
    return (o.getPersistentId());
  }

  void				update(T const &o, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);

    Database::getInstance()->getDb()->update(o);

    if (t) {
      t->commit();
      delete t;
    }
  }

  virtual void			smartUpdate(T &o, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    bool			isInTr = (t || inTr) ? true : false;

    if (o.isPersistent())
      this->update(o, isInTr);
    else
      this->persist(o, isInTr);

    if (t) {
      t->commit();
      delete t;
    }
  }

  void				erase(T const &o, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);

    Database::getInstance()->getDb()->erase(o);

    if (t) {
      t->commit();
      delete t;
    }
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

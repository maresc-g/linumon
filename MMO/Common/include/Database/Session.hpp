//
// Session.hpp for Session in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 17 14:49:11 2014 alexis mestag
// Last update Wed Feb 19 01:04:21 2014 alexis mestag
//

#ifndef				__SESSION_HPP__
# define			__SESSION_HPP__

# include			<map>
# include			<memory>
# include			<cassert>
# include			<typeinfo>
# include			<odb/database.hxx>
# include			<odb/traits.hxx>
# include			<odb/details/type-info.hxx>
# include			"Utility/Singleton.hpp"
# include			"Mutex/Mutex.hpp"

class				Session : public Singleton<Session>
{
  friend class			Singleton<Session>;

private:
  // Attr
  Mutex				*_mtx;

private:
  Session() : Singleton<Session>(),
	      _mtx(new Mutex) {
    _mtx->init();
  }
  virtual ~Session() {
    _mtx->destroy();
    delete _mtx;
  }

  /*
  ** Copy constructor and operator= shouldn't be used
  */
  Session(Session const &rhs) : Singleton<Session>() {
    *this = rhs;
  }
  Session			&operator=(Session const &rhs) {
    if (this != &rhs) {}
    return (*this);
  }

public:
  template <typename T>
  class cache_position
  {
  public:
    typedef std::map<typename odb::object_traits<T>::id_type,
		     typename odb::object_traits<T>::pointer_type>	t_map;
    typedef typename t_map::iterator					t_map_it;

  private:
    t_map			*_map;
    t_map_it			_it;

  public:
    cache_position() : _map(NULL) {}
    cache_position(t_map &map, t_map_it const &it) : _map(&map), _it(it) {}
    cache_position(cache_position const &rhs) {
      *this = rhs;
    }
    cache_position		&operator=(cache_position const &rhs) {
      if (this != &rhs) {
	_map = rhs._map;
	_it = rhs._it;
      }
      return (*this);
    }

    void			erase() const {
      if (_map)
	_map->erase(_it);
    }
  };

private:
  struct			object_map_base {};
  template<typename T>
  struct			object_map : public object_map_base
  {
    typename cache_position<T>::t_map	map;
  };

  typedef std::map<std::type_info const *,
		   object_map_base *,
		   odb::details::type_info_comparator>	map_type;

  map_type			_cache;

  /*
  ** Corresponding methods
  */
  template <typename T>
  cache_position<T>		cache_insert(odb::database &db __attribute__((unused)),
					     const typename odb::object_traits<T>::id_type &id,
					     const typename odb::object_traits<T>::pointer_type &obj) {
    // if no session
    // return (cache_position<T>()); // Handle it later

    object_map<T>		*pm;

    _mtx->lock();

    map_type::const_iterator	it = _cache.find(&typeid(T));

    if (it == _cache.end()) {
      pm = new object_map<T>;
      _cache[&typeid(T)] = pm;
    }
    else
      pm = static_cast<object_map<T> *>(it->second);

    typename cache_position<T>::t_map::value_type			vt(id, obj);
    std::pair<typename cache_position<T>::t_map::iterator, bool>	r = pm->map.insert(vt);

    _mtx->unlock();
    assert(r.second);
    return (cache_position<T>(pm->map, r.first));
  }

  template <typename T>
  typename odb::object_traits<T>::pointer_type
  cache_find(odb::database &db __attribute__((unused)),
	     const typename odb::object_traits<T>::id_type &id) {
    // if no session
    // return (odb::object_traits<T>::pointer_type()); // Handle it later

    _mtx->lock();

    map_type::iterator		it = _cache.find(&typeid(T));

    if (it != _cache.end()) {
      object_map<T> const				*pm = static_cast<object_map<T> const *>(it->second);
      typename cache_position<T>::t_map::const_iterator	jt = pm->map.find(id);

      if (jt != pm->map.end()) {
	_mtx->unlock();
	return (jt->second);
      }
    }
    _mtx->unlock();
    return (typename odb::object_traits<T>::pointer_type());
  }

  template <typename T>
  void				cache_erase(const cache_position<T> &p) {
    _mtx->lock();
    p.erase();
    _mtx->unlock();
  }

public:
  /*
  ** Cache management functions.
  */
  template <typename T>
  static cache_position<T>	_cache_insert(odb::database &db,
					      const typename odb::object_traits<T>::id_type &id,
					      const typename odb::object_traits<T>::pointer_type &obj) {
    return (Session::getInstance()->cache_insert<T>(db, id, obj));
  }

  template <typename T>
  static typename odb::object_traits<T>::pointer_type
  _cache_find(odb::database &db,
	      const typename odb::object_traits<T>::id_type &id) {
    return (Session::getInstance()->cache_find<T>(db, id));
  }

  template <typename T>
  static void			_cache_erase(const cache_position<T> &pos) {
    Session::getInstance()->cache_erase<T>(pos);
  }

  /*
  ** Notification functions.
  ** Theses are useless for now
  */
  template <typename T>
  static void			_cache_persist(const cache_position<T> &) {}

  template <typename T>
  static void			_cache_load(const cache_position<T> &) {}

  template <typename T>
  static void			_cache_update(odb::database &, const T &) {}

  template <typename T>
  static void			_cache_erase(odb::database &,
					     const typename odb::object_traits<T>::id_type &) {}
};

#endif

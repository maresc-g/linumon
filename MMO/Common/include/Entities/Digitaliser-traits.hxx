//
// Digitaliser-traits.hxx for Digitaliser-traits in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:28:35 2013 alexis mestag
// Last update Tue Dec 10 15:30:28 2013 alexis mestag
//

#ifndef			__DIGITALISER_TRAITS_HXX__
# define		__DIGITALISER_TRAITS_HXX__

# include		<odb/pre.hxx>
# include		<odb/container-traits.hxx>
# include		"Entities/Digitaliser.hh"

namespace		odb
{
  template<>
  class			access::container_traits<Digitaliser *>
  {
  public:
    static container_kind const			kind = ck_ordered;
    static bool const				smart = false;

    typedef Digitaliser *			container_type;

    typedef Mob *				value_type;
    typedef std::list<value_type>::size_type	index_type;

    typedef ordered_functions<index_type, value_type>   functions;

  public:
    static void		persist(container_type const &c, functions const &f) {
      index_type	i = 0;

      for (auto it = c->_mobs->cbegin() ; it != c->_mobs->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		load(container_type const &c, bool more, functions const &f) {
      c->_mobs->clear();

      while (more) {
	index_type	dummy;

	c->_mobs->push_back(value_type());
	more = f.select(dummy, c->_mobs->back());
      }
    }

    static void         update(container_type const &c, functions const &f) {
      f.delete_();

      index_type       i = 0;

      for (auto it = c->_mobs->cbegin() ; it != c->_mobs->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		erase(functions const &f) {
      f.delete_();
    }
  };
}

#endif

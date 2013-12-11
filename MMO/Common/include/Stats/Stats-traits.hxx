//
// Stats-traits.hxx for Stats-traits in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:19:02 2013 alexis mestag
// Last update Thu Dec  5 20:21:07 2013 alexis mestag
//

#ifndef			__STATS_TRAITS_HXX__
# define		__STATS_TRAITS_HXX__

# include		<odb/pre.hxx>
# include		<odb/container-traits.hxx>
# include		"Stats/Stats.hh"

namespace		odb
{
  template<>
  class			access::container_traits<Stats *>
  {
  public:
    static container_kind const			kind = ck_ordered;
    static bool const				smart = false;

    typedef Stats *				container_type;

    typedef Stat *				value_type;
    typedef std::list<Stat *>::size_type	index_type;

    typedef ordered_functions<index_type, value_type>   functions;

  public:
    static void		persist(container_type const &c, functions const &f) {
      index_type	i = 0;

      for (auto it = c->_stats->cbegin() ; it != c->_stats->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		load(container_type const &c, bool more, functions const &f) {
      c->_stats->clear();

      while (more) {
	index_type	dummy;

	c->_stats->push_back(value_type());
	more = f.select(dummy, c->_stats->back());
      }
    }

    static void         update(container_type const &c, functions const &f) {
      f.delete_();

      index_type       i = 0;

      for (auto it = c->_stats->cbegin() ; it != c->_stats->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		erase(functions const &f) {
      f.delete_();
    }
  };
}

#endif

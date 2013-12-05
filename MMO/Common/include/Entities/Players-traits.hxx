//
// Players-traits.hxx for Players-traits in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 11:15:26 2013 alexis mestag
// Last update Thu Dec  5 14:31:46 2013 alexis mestag
//

#ifndef			__PLAYERS_TRAITS_HXX__
# define		__PLAYERS_TRAITS_HXX__

# include		<odb/pre.hxx>
# include		<odb/container-traits.hxx>
# include		"Entities/Players.hh"

namespace		odb
{
  template<>
  class			access::container_traits<Players *>
  {
  public:
    static container_kind const			kind = ck_ordered;
    static bool const				smart = false;

    typedef Players *				container_type;

    typedef Player *				value_type;
    typedef std::list<Player *>::size_type	index_type;

    typedef ordered_functions<index_type, value_type>   functions;

  public:
    static void		persist(container_type const &c, functions const &f) {
      index_type	i = 0;

      for (auto it = c->_players->cbegin() ; it != c->_players->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		load(container_type const &c, bool more, functions const &f) {
      c->_players->clear();

      while (more) {
	index_type	dummy;

	c->_players->push_back(value_type());
	more = f.select(dummy, c->_players->back());
      }
    }

    static void         update(container_type const &c, functions const &f) {
      f.delete_();

      index_type       i = 0;

      for (auto it = c->_players->cbegin() ; it != c->_players->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		erase(functions const &f) {
      f.delete_();
    }
  };
}

#endif

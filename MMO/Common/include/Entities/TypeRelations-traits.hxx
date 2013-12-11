//
// TypeRelations-traits.hxx for TypeRelations-traits in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common/include/Entities
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  9 19:34:54 2013 alexis mestag
// Last update Tue Dec 10 13:17:39 2013 alexis mestag
//

#ifndef			__TYPERELATIONS_TRAITS_HXX__
# define		__TYPERELATIONS_TRAITS_HXX__

# include		<odb/pre.hxx>
# include		<utility>
# include		<odb/container-traits.hxx>
# include		<odb/details/config.hxx>

# include		"Entities/Type.hh"

namespace		odb
{
  template<>
  class			access::container_traits<TypeRelations *>
  {
  public:
    static container_kind const			kind = ck_ordered;
    static bool const				smart = false;

    typedef TypeRelations *			container_type;

    typedef Type::Link				value_type;
    typedef std::list<value_type>::size_type	index_type;

    typedef ordered_functions<index_type, value_type>	functions;

  public:
    static void		persist(container_type const &c, functions const &f) {
      index_type	i = 0;

      for (auto it = c->_relations->cbegin() ; it != c->_relations->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		load(container_type &c, bool more, functions const &f) {
      c->_relations->clear();

      while (more) {
	index_type	dummy;

	c->_relations->push_back(value_type());
	more = f.select(dummy, c->_relations->back());
      }
    }

    static void		update(container_type const &c, functions const &f) {
      f.delete_();

      index_type	i = 0;

      for (auto it = c->_relations->cbegin() ; it != c->_relations->cend() ; ++it) {
	f.insert(i++, *it);
      }
    }

    static void		erase(functions const &f) {
      f.delete_();
    }
  };
}

# include		<odb/post.hxx>

#endif

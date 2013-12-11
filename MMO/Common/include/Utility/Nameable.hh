//
// Nameable.hh for Nameable in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:45:38 2013 alexis mestag
// Last update Tue Dec 10 14:46:36 2013 alexis mestag
//

#ifndef			__NAMEABLE_HH__
# define		__NAMEABLE_HH__

# include		<odb/core.hxx>
# include		<string>

class			Nameable
{
  // friend class		odb::access;

private:
  std::string		_name;

public:
  Nameable(std::string const &name = "");
  Nameable(Nameable const &rhs);
  virtual ~Nameable();

  Nameable		&operator=(Nameable const &rhs);

  std::string const	&getName() const;
  void			setName(std::string const &name);
};

# ifdef	ODB_COMPILER
#  pragma db object(Nameable) abstract
#  pragma db member(Nameable::_name)
# endif

#endif

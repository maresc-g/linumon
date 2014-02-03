//
// Id.hh for Id in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:54:26 2013 alexis mestag
// Last update Fri Jan 31 14:19:03 2014 laurent ansel
//

#ifndef			__ID_HH__
# define		__ID_HH__

class			Id
{
private:
  unsigned long		_id;

public:
  Id();
  Id(Id const &rhs);
  virtual ~Id();
  Id			&operator=(Id const &rhs);

  unsigned long		getId() const;
  void			setId(unsigned long const id);
};

#endif

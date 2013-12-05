//
// Id.hh for Id in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Dec  2 16:54:26 2013 alexis mestag
// Last update Tue Dec  3 10:48:07 2013 alexis mestag
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

//
// AMutex.hh for AMutex in /home/mestag_a/Documents/Projets/Tek3/Babel/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov 25 21:12:38 2013 alexis mestag
// Last update Mon Nov 25 22:38:41 2013 alexis mestag
//

#ifndef			__AMUTEX_HH__
# define		__AMUTEX_HH__

#include		"Mutex/IMutex.hh"

class			AMutex : public IMutex
{
private:
  // This attribute is deliberately private.
  // It will be set to true in the init() methods of subclasses.
  //	=> It's its only purpose, it SHOULDN'T be set anywhere else.
  // Even though you wan't to set it somewhere else, DON'T make it protected,
  // use the setIsInit() method below, which is protected.
  // Thanks in advance.
  bool			_isInit;

protected:
  AMutex();
  virtual ~AMutex();

  void			setIsInit(bool const init = true);

public:
  bool			isInit() const;
};

#endif

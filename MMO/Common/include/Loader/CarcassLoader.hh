//
// CarcassLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar 14 15:04:24 2014 laurent ansel
// Last update Fri Mar 14 15:05:04 2014 laurent ansel
//

#ifndef 			__CARCASSLOADER_HH__
# define 			__CARCASSLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Carcass.hh"

class				Carcasss
{
public:
  typedef Carcass		value;

private:
  void				setCarcasss(std::list<Carcass *> const &carcasss);

private:
  std::list<Carcass *>		*_carcasss;

public:
  Carcasss();
  virtual ~Carcasss();

  std::list<Carcass *> const	&getCarcasss() const;

  void				addCarcass(Carcass *carcass);

  Carcass			*getCarcass(std::string const &name) const;
  Carcass			*getCarcass(unsigned int const id) const;
};

class				CarcassLoader : public ILoader<Carcasss>
{
private:
  Carcasss			*_carcasss;
public:
  CarcassLoader();
  virtual ~CarcassLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual Carcasss const	&getLoaderContent() const;
  virtual Carcasss::value	*getValue(std::string const &name) const;
  virtual Carcasss::value	*getValue(unsigned int const id) const;
};

#endif

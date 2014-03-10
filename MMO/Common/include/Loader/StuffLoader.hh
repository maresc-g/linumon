//
// StuffManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 11:09:06 2014 laurent ansel
// Last update Thu Mar  6 11:55:42 2014 laurent ansel
//

#ifndef 			__STUFFLOADER_HH__
# define 			__STUFFLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Stuff.hh"

class				Stuffs
{
public:
  typedef Stuff			value;

private:
  void				setStuffs(std::list<Stuff *> const &stuffs);

private:
  std::list<Stuff *>		*_stuffs;

public:
  Stuffs();
  virtual ~Stuffs();

  std::list<Stuff *> const	&getStuffs() const;

  void				addStuff(Stuff *stuff);

  Stuff				*getStuff(std::string const &name) const;
  Stuff				*getStuff(unsigned int const id) const;
};

class				StuffLoader : public ILoader<Stuffs>
{
private:
  Stuffs			*_stuffs;
public:
  StuffLoader();
  virtual ~StuffLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual Stuffs const		&getLoaderContent() const;
  virtual Stuffs::value		*getValue(std::string const &name) const;
  virtual Stuffs::value		*getValue(unsigned int const id) const;
};

#endif

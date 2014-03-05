//
// ILoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 11:50:29 2014 laurent ansel
// Last update Wed Mar  5 14:29:15 2014 laurent ansel
//

#ifndef 			__ILOADER_HH__
# define 			__ILOADER_HH__

#include			"Utility/Nameable.hh"
#include			"Utility/ISerialization.hh"

template<typename T>
class				ILoader : public Nameable, public ISerialization
{
public:
  virtual ~ILoader(){}
  virtual bool			serialization(Trame &trame) const = 0;
  virtual bool			deserialization(Trame &trame) = 0;
  virtual T const		&getLoaderContent() const = 0;
  virtual typename T::value	*getValue(std::string const &name) const = 0;
  virtual typename T::value	*getValue(unsigned int const id) const = 0;
};

#endif

//
// FunctorContainer.hpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Dec 13 16:59:13 2013 laurent ansel
// Last update Fri Dec 13 17:29:32 2013 laurent ansel
//

#ifndef 			__FUNCTORCONTAINER_HPP__
# define 			__FUNCTORCONTAINER_HPP__

#include			<string>
#include			<map>
#include			<functional>
#include			<boost/any.hpp>

template<typename K, typename RET>
class				FunctorContainer
{
private:
  std::map<K, boost::any>	*_function;
public:
  FunctorContainer():
    _function(new std::map<K, boost::any>)
  {

  }

  virtual ~FunctorContainer()
  {
    delete _function;
  }

  template<typename... P>
  bool				load(K const &key, RET (*func)(P...))
  {
    std::function<RET (P...)>	f = func;
    (*_function)[key] = f;
    return (true);
  }

  template<typename... P>
  bool				load(K const &key, std::function<RET (P...)> const &func)
  {
    (*_function)[key] = func;
    return (true);
  }

  template<typename... P>
  RET				operator()(K const key, P ... params)
  {
    return (boost::any_cast<std::function<RET (P...)> >((*_function)[key])(params ...));
  }
};

#endif

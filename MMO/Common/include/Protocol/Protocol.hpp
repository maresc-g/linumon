//
// Protocole.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec 12 13:29:12 2013 laurent ansel
// Last update Sat Dec 14 19:12:16 2013 laurent ansel
//

#ifndef 			__PROTOCOL_HPP__
# define 			__PROTOCOL_HPP__

#include			<sstream>
#include			<fstream>
#include			<list>
#include			"Utility/FunctorContainer.hpp"
#include			"Trame/Trame.hh"

template<typename K> //KEY
class				Protocol
{
private:
  FunctorContainer<K, bool>	*_container;
  std::map<K, std::list<std::string> *>	*_parametersType;
public:
  Protocol():
    _container(new FunctorContainer<std::string, bool>),
    _parametersType(new std::map<K, std::list<std::string> *>)
  {

  }

  // Protocol(std::string const &filename):
  //   _container(new FunctorContainer<std::string, bool>),
  //   _parametersType(new std::map<K, std::list<std::string> *>)
  // {
  //   this->load(filename);
  // }

  virtual ~Protocol()
  {
    delete _container;
    for (auto it = _parametersType->begin() ; it != _parametersType->end() ; ++it)
      delete it->second;
    delete _parametersType;
  }

  template<typename R, typename... P>
  bool				addNewFunction(K const &key, R (*func)(P...))
  {
    _container->load(key, func);
    return (true);
  }

  template<typename R, typename... P>
  bool				addNewFunction(K const &key, std::function<R (P...)> func)
  {
    _container->load(key, func);
    return (true);
  }

  bool				newParameters(K const &key, std::string const &param)
  {
    if (_parametersType->find(key) == _parametersType->end())
      (*_parametersType)[key] = new std::list<std::string>;
    (*_parametersType)[key]->push_back(param);
    return (true);
  }

  bool				newParameters(K const &key, std::list<std::string> const &params)
  {
    if (_parametersType->find(key) == _parametersType->end())
      (*_parametersType)[key] = new std::list<std::string>;
    for (auto it = params.begin() ; it != params.end() ; ++it)
      (*_parametersType)[key]->push_back(*it);
    return (true);
  }

  std::list<std::string>	&getListParameters(K const &key)
  {
    return (*(*_parametersType)[key]);
  }

  // bool				load(std::string const &filename)
  // {
  //   bool			ret;
  //   Json::Value			value;
  //   std::ifstream		str(filename, std::ifstream::binary);
  //   Json::Reader		*reader = new Json::Reader;
  //   std::vector<std::string>	list;

  //   ret = reader->parse(str, value);
  //   std::cout << "ret = " << ret << std::endl;
  //   std::cout << "{" << std::endl;
  //   list  = value.getMemberNames();
  //   for (auto it = list.begin() ; it != list.end() ; it++)
  //     {
  //   	std::cout << (*it) << std::endl;
  //     }
  //   std::cout << "}" << std::endl;
  //   return (ret);
  // }
};

#endif

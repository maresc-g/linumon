//
// GenericSerialization.hpp for SERIAL in /home/maitre_c/work/linumon/MMO/Common/include/Utility
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Thu Feb  6 11:14:11 2014 antoine maitre
// Last update Thu Feb  6 15:01:10 2014 antoine maitre
//

#ifndef				__GENERICSERIALIZATION_HPP__
# define			__GENERICSERIALIZATION_HPP__

# include			<list>
# include			<sstream>
# include			"ISerialization.hh"

template <typename T>
void				serialList(Trame &trame, std::list<T *> &list)
{
  int i = 0;
  for (auto it = list.begin(); it != list.end(); it++)
    {
      (*it)->serialization(trame(trame["LIST"][i]));
      i++;
    }
}

template <typename T>
std::list<T *>			unserialList(Trame const &trame)
{
  std::list<T *>		ret;

  for (int i = 0; trame["LIST"].isMember(std::to_string(i)); i++)
    ret.push_back(T::deserialization(trame(trame["LIST"][i])));
  return (ret);
}

#endif 

//
// Stack.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar 12 14:05:11 2014 laurent ansel
// Last update Sat Mar 15 11:18:43 2014 laurent ansel
//

#include			"Entities/Stack.hh"
#include			"Loader/LoaderManager.hh"

AItem				*getItemLoader(std::string const &name)
{
  return (LoaderManager::getInstance()->getItemLoader(name));
}

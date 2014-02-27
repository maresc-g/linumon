//
// HesodeEffect.cpp for HesodeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:55:45 2014 alexis mestag
// Last update Wed Feb 26 23:54:02 2014 alexis mestag
//

#include				"HesodeEffect.hh"
#include				<iostream>

HesodeEffect::HesodeEffect() :
  PlayerEffect()
{

}

HesodeEffect::~HesodeEffect()
{

}

#include		"Database/Repositories/StatKeyRepository.hpp"

bool					HesodeEffect::apply(Player &player)
{
Repository<StatKey>		*rsk = &Database::getRepository<StatKey>();

std::cout << "HesodeEffect::Repo : " << (void *)rsk << std::endl;
  player.setStat("Attack", 10, true);
  return (true);
}

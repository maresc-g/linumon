//
// GameProtocol.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 14:20:20 2014 laurent ansel
// Last update Wed Feb 12 20:37:56 2014 laurent ansel
//

#include			"GameProtocol/GameProtocol.hh"

GameProtocol::GameProtocol():
  _interaction(new Interaction),
  _inventory(new InventoryManager),
  _job(new JobManager),
  _other(new OtherCommand),
  _stuff(new StuffActions),
  _talent(new TalentManager)
{
}

GameProtocol::~GameProtocol()
{
  delete _interaction;
  delete _inventory;
  delete _job;
  delete _other;
  delete _stuff;
  delete _talent;
}

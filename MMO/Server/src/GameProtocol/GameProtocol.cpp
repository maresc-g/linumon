//
// GameProtocol.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 14:20:20 2014 laurent ansel
// Last update Thu Mar 13 20:23:19 2014 laurent ansel
//

#include			"GameProtocol/GameProtocol.hh"

GameProtocol::GameProtocol():
  _interaction(new Interaction),
  _inventory(new InventoryManager),
  _job(new JobManager),
  _other(new OtherCommand),
  _stuff(new StuffActions),
  _talent(new TalentManager),
  _digitaliser(new DigitaliserManager),
  _guild(new GuildManager)
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

//
// GameProtocol.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 14:07:25 2014 laurent ansel
// Last update Sat Feb  8 18:07:21 2014 laurent ansel
//

#ifndef 			__GAMEPROTOCOL_HH__
# define 			__GAMEPROTOCOL_HH__

#include			"GameProtocol/Interaction.hh"
#include			"GameProtocol/InventoryManager.hh"
#include			"GameProtocol/JobManager.hh"
#include			"GameProtocol/OtherCommand.hh"
#include			"GameProtocol/StuffActions.hh"
#include			"GameProtocol/TalentManager.hh"
#include			"GameProtocol/Trade.hh"

class				GameProtocol
{
private:
  Interaction			*_interaction;
  InventoryManager		*_inventory;
  JobManager			*_job;
  OtherCommand			*_other;
  StuffActions			*_stuff;
  TalentManager			*_talent;
  Trade				*_trade;
public:
  GameProtocol();
  virtual ~GameProtocol();
};

#endif

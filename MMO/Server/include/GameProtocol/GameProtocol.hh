//
// GameProtocol.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 14:07:25 2014 laurent ansel
// Last update Wed Feb 12 20:32:20 2014 laurent ansel
//

#ifndef 			__GAMEPROTOCOL_HH__
# define 			__GAMEPROTOCOL_HH__

#include			"GameProtocol/Interaction.hh"
#include			"GameProtocol/InventoryManager.hh"
#include			"GameProtocol/JobManager.hh"
#include			"GameProtocol/OtherCommand.hh"
#include			"GameProtocol/StuffActions.hh"
#include			"GameProtocol/TalentManager.hh"

class				GameProtocol
{
private:
  Interaction			*_interaction;
  InventoryManager		*_inventory;
  JobManager			*_job;
  OtherCommand			*_other;
  StuffActions			*_stuff;
  TalentManager			*_talent;
public:
  GameProtocol();
  virtual ~GameProtocol();
};

#endif

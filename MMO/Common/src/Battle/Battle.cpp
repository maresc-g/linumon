//
// Battle.cpp for Battle in /home/maitre_c/work/linumon/MMO/Common/src/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 15:37:55 2014 antoine maitre
// Last update Wed Jan 29 16:58:59 2014 antoine maitre
//

#include				"Battle/Battle.hh"

Battle::Battle(unsigned int const id, eBattle const type, int const mobNumber, Player *player1, Player *player2)
  : _id(id), _type(type),
    _mobNumber(mobNumber),
    _mobs1(player1->getDigitaliser().getMobs()),
    _mobs2(player2->getDigitaliser().getMobs()), 
    _player1(player1),
    _player2(player2)
{
  
}

Battle::~Battle()
{
  
}


unsigned int				Battle::getID() const
{
  return (this->_id);
}

Battle::eBattle 			Battle::getType() const
{
  return (this->_type);
}


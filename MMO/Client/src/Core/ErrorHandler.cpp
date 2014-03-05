//
// ErrorHandler.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 13:06:46 2014 guillaume marescaux
// Last update Tue Mar  4 13:09:00 2014 guillaume marescaux
//

#include			"Core/ErrorHandler.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

ErrorHandler::ErrorHandler()
{
}

ErrorHandler::~ErrorHandler()
{
}

//------------------------------------END CTOR / DTOR------------------------------------------

//---------------------------------BEGIN PRIVATE METHODS---------------------------------------

void				ErrorHandler::badUsernamePass(MutexVar<CLIENT::eState> *state)
{
  *state = CLIENT::NONE;
}

void				ErrorHandler::userConnected(MutexVar<CLIENT::eState> *state)
{
  *state = CLIENT::NONE;
}

void				ErrorHandler::nameExists(MutexVar<CLIENT::eState> *state)
{
  *state = CLIENT::CHOOSE_PLAYER;
}

//----------------------------------END PRIVATE METHODS----------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				ErrorHandler::handleError(Error const &error, MutexVar<CLIENT::eState> *state)
{
  static std::map<Error::eError, void (ErrorHandler::*)(MutexVar<CLIENT::eState> *)>	ptrs =
    {
      { Error::USER, &ErrorHandler::badUsernamePass },
      { Error::USERCONNECTED, &ErrorHandler::userConnected },
      { Error::CREATEPLAYER, &ErrorHandler::nameExists }
    };

  if (ptrs.find(error.getType()) != ptrs.end())
    (this->*ptrs[error.getType()])(state);
}

//--------------------------------------END METHODS--------------------------------------------
